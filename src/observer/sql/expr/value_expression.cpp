#include "value_expression.h"
#include "sql/expr/tuple.h"

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

std::string ValueExpr::to_string() const {
  return value_.to_string();
}