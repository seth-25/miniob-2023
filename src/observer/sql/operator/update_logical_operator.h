#pragma once

#include <utility>
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
  UpdateLogicalOperator(Table *table, std::vector<Value>&& values, std::vector<const FieldMeta *>&& fields)
      : table_(table), values_(std::move(values)), fields_(std::move(fields)) {};
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table *table() const { return table_; }
  std::vector<Value>&  values()  { return values_; }
  std::vector<const FieldMeta *>&  fields() { return fields_; }

private:
  Table                         *table_ = nullptr;
  std::vector<Value>             values_;
  std::vector<const FieldMeta *> fields_;
};