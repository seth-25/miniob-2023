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
  UpdatePhysicalOperator(Table *table, const Value& value, std::vector<const FieldMeta *> &&fields)
      : table_(table), value_(value), fields_(std::move(fields))
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
  Value                          value_;
  std::vector<const FieldMeta *> fields_;
};
