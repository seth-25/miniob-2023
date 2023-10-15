#pragma once

#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief update逻辑算子
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, Value value, std::vector<const FieldMeta *> fields);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table *table() const { return table_; }
  Value  value() const { return value_; }
  std::vector<const FieldMeta *>&  fields() { return fields_; }

private:
  Table                         *table_ = nullptr;
  Value                          value_;
  std::vector<const FieldMeta *> fields_;
};