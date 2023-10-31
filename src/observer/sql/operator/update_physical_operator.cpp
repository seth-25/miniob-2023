#include "common/log/log.h"
#include "sql/operator/update_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "common/lang/typecast.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  trx_ = trx;

  // 将表达式转化成value
  for (int i = 0; i < exprs_.size(); i ++ ) {
    auto& expr = exprs_[i];
    Value value;
    EmptyTuple empty_tuple;
    rc = expr->get_value(empty_tuple, value);
    if (rc == RC::RECORD_EOF) { // 子查询没查到，但此时如果update的where不存在数据，应该返回success；如果update的字段可以为null，设为null
      rc = RC::SUCCESS;
    }
    if (rc == RC::RECORD_EXIST) { // 子查询没查到，但此时如果update的where不存在数据，应该返回success；存在数据则返回fail
      sub_query_return_more_than_one_row = true;
      rc = RC::SUCCESS;
    }
    if (rc != RC::SUCCESS) {
      return rc;
    }
    values_.emplace_back(value);
  }
  // 检查类型是否合法
  for (int i = 0; i < fields_.size(); i ++ ) {
    const AttrType field_type = fields_[i]->type();
    const AttrType value_type = values_[i].attr_type();
    if (AttrType::NULLS == value_type) {
      if (!fields_[i]->nullable()) {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      continue;
    }
    if (field_type != value_type && !common::type_cast_check(value_type, field_type) &&
        !TextHelper::isInsertText(field_type, value_type)) {
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    if (sub_query_return_more_than_one_row) {  // 子查询超过一行，update的where存在数据，应该返回fail
      return RC::INTERNAL;
    }
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &old_record = row_tuple->record();

    // 将old_record的值更新成新的值
    Record new_record;
    rc = table_->make_record_from_old_record(fields_, values_, old_record, new_record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to make update record: %s", strrc(rc));
      return rc;
    }
    rc = trx_->update_record(table_, old_record, new_record, fields_); //todo
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
