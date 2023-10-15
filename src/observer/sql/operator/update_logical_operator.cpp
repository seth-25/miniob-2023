#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, Value value, std::vector<const FieldMeta *> fields)
    : table_(table), value_(value), fields_(fields)
{}