#include "aggregation_expression.h"

#include <memory>
#include "tuple_cell.h"
#include "tuple.h"
#include "value_expression.h"

RC AggrFuncExpr::create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr,
    const std::unordered_map<std::string, TableUnit*> &table_map, const TableUnit* default_table)
{
  assert(ExprSqlNodeType::AGGREGATION == expr->type);
  bool with_brace = expr->with_brace;
  AggrExprSqlNode* aggr_expr_node = expr->aggr_expr;
  if (ExprSqlNodeType::UNARY == aggr_expr_node->expr->type && !aggr_expr_node->expr->unary_expr->is_attr) {
    // count(*) count(1) count(Value)
    assert(AggrFuncType::AGGR_COUNT == aggr_expr_node->type);
    std::unique_ptr<Expression> value_exp = nullptr;  // *或1用value表达式
    RC rc = Expression::create_expression(aggr_expr_node->expr, value_exp, table_map, default_table);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("AggrFuncExpr Create Param Expression Failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
    assert(ExprType::VALUE == value_exp->type());
    TableUnit* table_unit = table_map.begin()->second;
    std::unique_ptr<Expression> field_expr;
    if (table_unit->is_table()) {
      const Table* table = table_unit->table();
      field_expr = std::make_unique<FieldExpr>(table, table->table_meta().field(0));  // todo 可能需要修改count的field是哪列
    }
    else {
      SelectStmt* view_stmt = table_unit->view_stmt();
      std::shared_ptr<Expression> view_expr = view_stmt->project_expres()[0];
      field_expr = std::make_unique<FieldExpr>(view_expr, table_unit->view_name());
    }

    std::unique_ptr<AggrFuncExpr> aggr_func_expr(new AggrFuncExpr(
        AggrFuncType::AGGR_COUNT, std::move(field_expr), std::move(value_exp), with_brace));
    res_expr = std::move(aggr_func_expr);
    return RC::SUCCESS;
  }
  std::unique_ptr<Expression> param = nullptr;
  RC rc = Expression::create_expression(aggr_expr_node->expr, param, table_map, default_table);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("AggrFuncExpr Create Param Expression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  assert(nullptr != param && ExprType::FIELD == param->type());
  std::unique_ptr<AggrFuncExpr> aggr_func_expr(new AggrFuncExpr(aggr_expr_node->type, std::move(param), with_brace));
  res_expr = std::move(aggr_func_expr);
  return RC::SUCCESS;
}

std::string AggrFuncExpr::get_func_name() const
{
  switch (aggr_type_) {
    case AggrFuncType::AGGR_MAX:
      return "max";
    case AggrFuncType::AGGR_MIN:
      return "min";
    case AggrFuncType::AGGR_SUM:
      return "sum";
    case AggrFuncType::AGGR_AVG:
      return "avg";
    case AggrFuncType::AGGR_COUNT:
      return "count";
    default:
      break;
  }
  return "unknown_aggr_fun";
}

std::string AggrFuncExpr::to_string(bool with_table_name) {
  std::string result_name;
  result_name += get_func_name();
  result_name += '(';
  if (is_param_value()) {
    result_name += ((ValueExpr*) value_expr_.get())->to_string();
  } else {
    result_name += ((FieldExpr*)field_expr().get())->to_string(with_table_name);
  }
  result_name += ')';
  return result_name;
}


RC AggrFuncExpr::get_value(const Tuple &tuple, Value &value) const {
  FieldExpr* field_expr = (FieldExpr *)field_expr_.get();
  if (field_expr->is_table()) {
    std::unique_ptr<FieldExpr> field_expr_copy = std::make_unique<FieldExpr>(field_expr->field());
    field_expr_copy->set_aggr(aggr_type_);
    return tuple.find_cell(TupleCellSpec(std::move(field_expr_copy)), value);
  }
  else {
    std::unique_ptr<FieldExpr> field_expr_copy = std::make_unique<FieldExpr>(field_expr->view_expr(), field_expr->table_name());
    field_expr_copy->set_aggr(aggr_type_);
    return tuple.find_cell(TupleCellSpec(std::move(field_expr_copy)), value);
  }
}

