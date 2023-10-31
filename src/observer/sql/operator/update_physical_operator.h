#pragma once

#include <utility>

#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, std::vector<std::unique_ptr<Expression>>&& exprs, std::vector<const FieldMeta *> &&fields)
      : table_(table), exprs_(std::move(exprs)), fields_(std::move(fields))
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table                         *table_ = nullptr;
  Trx                           *trx_   = nullptr;
  std::vector<std::unique_ptr<Expression>> exprs_;
  std::vector<const FieldMeta *> fields_;
  std::vector<Value> values_;
  int sub_query_return_row = 0; // 0 子查询没查到，1子查询有且仅有1条，2子查询查到多条数据
};
