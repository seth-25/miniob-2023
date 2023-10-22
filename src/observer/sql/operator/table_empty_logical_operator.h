
#include "sql/operator/logical_operator.h"

class TableEmptyLogicalOperator : public LogicalOperator
{
public:
  TableEmptyLogicalOperator() = default;
  virtual ~TableEmptyLogicalOperator() = default;

  LogicalOperatorType type() const override {
    return LogicalOperatorType::TABLE_EMPTY;
  }
};
