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
  UpdateLogicalOperator(Table *table, std::vector<std::unique_ptr<Expression>>&& exprs, std::vector<const FieldMeta *>&& fields)
      : table_(table), exprs_(std::move(exprs)), fields_(std::move(fields)) {};
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table *table() const { return table_; }
  std::vector<std::unique_ptr<Expression>>&  exprs()  { return exprs_; }
  std::vector<const FieldMeta *>&  fields() { return fields_; }

private:
  Table                         *table_ = nullptr;
  std::vector<std::unique_ptr<Expression>> exprs_;
  std::vector<const FieldMeta *> fields_;
};