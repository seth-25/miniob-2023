#include "tuple.h"
#include "aggregation_expression.h"

void GroupTuple::do_aggregate_empty() {
  assert(aggr_results_.size() == aggr_exprs_.size());
  assert(aggr_exprs_.size() == aggr_all_null_.size());
  assert(aggr_exprs_.size() == aggr_counts_.size());
  assert(field_results_.size() == field_exprs_.size());
  for (size_t i = 0; i < aggr_exprs_.size(); i ++ ) {
    AggrFuncExpr* aggr_expr = (AggrFuncExpr*) aggr_exprs_[i].get();
    Value value = Value(0);
    if (aggr_expr->aggr_type() == AggrFuncType::AGGR_COUNT) {
      aggr_results_[i] = value;
    }
    else {
      value.set_null();
      aggr_results_[i] = value;
    }
  }
}

void GroupTuple::do_aggregate_first()
{
  assert(aggr_results_.size() == aggr_exprs_.size());
  assert(aggr_exprs_.size() == aggr_all_null_.size());
  assert(aggr_exprs_.size() == aggr_counts_.size());
  assert(field_results_.size() == field_exprs_.size());
  // first row in current group
  for (size_t i = 0; i < aggr_all_null_.size(); ++i) {
    aggr_all_null_[i] = true;
    aggr_counts_[i] = 0;
  }
  for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
    const AggrFuncExpr *aggr_expr = (AggrFuncExpr*) aggr_exprs_[i].get();
    aggr_expr->get_value(*tuple_, aggr_results_[i]);
    if (!aggr_results_[i].is_null()) {
      aggr_all_null_[i] = false;
      aggr_counts_[i]++;
    }
  }
  for (size_t i = 0; i < field_exprs_.size(); ++i) {
    field_exprs_[i]->get_value(*tuple_, field_results_[i]);
  }
}

void GroupTuple::do_aggregate()
{
  Value tmp;
  for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
    const AggrFuncExpr *aggr_expr = (AggrFuncExpr*) aggr_exprs_[i].get();
    aggr_expr->get_value(*tuple_, tmp);
    if (tmp.is_null()) {  // cannot do any aggregate for NULL
      continue;
    }
    aggr_all_null_[i] = false;
    aggr_counts_[i]++;
    if (AggrFuncType::AGGR_COUNT == aggr_expr->aggr_type()) {
      continue;
    }
    // NOTE: aggr_results_[i] maybe null. tmp is not null
    if (aggr_results_[i].is_null()) {
      aggr_results_[i] = tmp;
    }
    switch (aggr_expr->aggr_type()) {
      case AggrFuncType::AGGR_MIN:
        aggr_results_[i] = Value::calc_min(aggr_results_[i], tmp);
        break;
      case AggrFuncType::AGGR_MAX:
        aggr_results_[i] = Value::calc_max(aggr_results_[i], tmp);
        break;
      case AggrFuncType::AGGR_SUM:
      case AggrFuncType::AGGR_AVG:
        aggr_results_[i] = Value::calc_add(aggr_results_[i], tmp);
        break;
      default:
        LOG_ERROR("Unsupported AggrFuncType");
        break;
    }
  }
}

void GroupTuple::do_aggregate_done()
{
  for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
    const AggrFuncExpr *aggr_expr = (AggrFuncExpr *)aggr_exprs_[i].get();
    Value &res = aggr_results_[i];
    // if all null, result is null
    if (aggr_all_null_[i] && AggrFuncType::AGGR_COUNT != aggr_expr->aggr_type()) {
      aggr_results_[i].set_null();
      continue;
    }
    switch (aggr_expr->aggr_type()) {
      case AggrFuncType::AGGR_COUNT: {
        res.set_type(AttrType::INTS);
        res.set_int(aggr_counts_[i]);
        break;
      }
      case AggrFuncType::AGGR_AVG: {
        Value cnt = Value(aggr_counts_[i]);
        res = Value::calc_div(res, cnt);
        break;
      }
      default:
        break;
    }
  }
}

RC GroupTuple::find_cell(const TupleCellSpec &spec, Value &value) const
{
  if (tuple_ == nullptr) {
    return RC::EMPTY;
  }
  assert(spec.expression()->type() == ExprType::FIELD);
  FieldExpr *field_expr = (FieldExpr *)spec.expression(); // 查询的field
  if (field_expr->with_aggr()) {
    for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
      AggrFuncExpr *aggr_expr = (AggrFuncExpr *)(aggr_exprs_[i].get());
      if (field_expr->field().equal(aggr_expr->field()) && aggr_expr->aggr_type() == field_expr->get_aggr_type()) {
        value = aggr_results_[i];
        LOG_INFO("Field is found in aggr_exprs");
        return RC::SUCCESS;
      }
    }
  }
  for (size_t i = 0; i < field_exprs_.size(); ++i) {  // 所有需要group by的field
    FieldExpr *expr = (FieldExpr *)field_exprs_[i].get();
    if (field_expr->field().equal(expr->field())) {
      value = field_results_[i];
      LOG_INFO("Field is found in field_exprs");
      return RC::SUCCESS;
    }
  }
  return RC::NOTFOUND;
}