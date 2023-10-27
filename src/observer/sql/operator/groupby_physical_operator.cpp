#include "groupby_physical_operator.h"

RC GroupByPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  if (RC::SUCCESS != (rc = children_[0]->open(trx))) {
    rc = RC::INTERNAL;
    LOG_WARN("SortOperater child open failed!");
  }
  tuple_.set_tuple(children_[0]->current_tuple());
  is_record_eof_ = false;
  is_first_ = true;
  is_new_group_ = true;
  return rc;
}
RC GroupByPhysicalOperator::next()
{
  if (is_record_eof_) {
    return RC::RECORD_EOF;
  }
  RC rc = RC::SUCCESS;

  if (is_first_) {
    rc = children_[0]->next();
    is_first_ = false;
    is_new_group_ = true;
    if (RC::RECORD_EOF == rc) { // 第一次执行就没有record，如果是count需要打印0，如果是avg sum max min需要打印NULL
      tuple_.do_aggregate_empty();
      is_record_eof_ = true;
      return RC::SUCCESS;
    }
    // set initial value of pre_values_
    for (auto& field_expr : group_by_field_exprs_) {
      pre_values_.emplace_back(Value());
      field_expr->get_value(*children_[0]->current_tuple(), pre_values_.back());
    }
    assert(pre_values_.size() == group_by_field_exprs_.size());
    LOG_INFO("GroupByOperator set first success!");
  }

  while (true) {
    // 0. if the last row is new group, do aggregate first
    if (is_new_group_) {
      tuple_.do_aggregate_first();
      is_new_group_ = false;
    }
    if (RC::SUCCESS != (rc = children_[0]->next())) {
      break;
    }
    // 1. adjust whether current tuple is new group or not
    for (size_t i = 0; i < group_by_field_exprs_.size(); ++i) {
      auto&field_expr = group_by_field_exprs_[i];
      Value value;
      field_expr->get_value(*children_[0]->current_tuple(), value);
      if (value != pre_values_[i] && !(value.is_null() && pre_values_[i].is_null())) {  // 两个null看作相等
        // 2. update pre_values_ and set new group
        pre_values_[i] = value;
        is_new_group_ = true;
      }
    }
    // 3. if new group, should return a row
    if (is_new_group_) {
      tuple_.do_aggregate_done();
      return rc;
    }
    // 4. if not new group, execute aggregate function and update result
    tuple_.do_aggregate();
  }

  if (RC::RECORD_EOF == rc) {
    is_record_eof_ = true;
    tuple_.do_aggregate_done();
    return RC::SUCCESS;
  }

  return rc;
}
RC GroupByPhysicalOperator::close()
{
  RC rc = RC::SUCCESS;
  children_[0]->close();
  return rc;return RC::RECORD_EOF;
}
Tuple *GroupByPhysicalOperator::current_tuple() { return &tuple_; }
