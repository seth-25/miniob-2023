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
RC ValueExpr::create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr)
{
  assert(expr->type == ExprSqlNodeType::UNARY);
  bool with_brace = expr->with_brace;
  UnaryExprSqlNode *unary_expr = expr->unary_expr;
  assert(unary_expr->is_attr == false);
  std::unique_ptr<ValueExpr> tmp(new ValueExpr(unary_expr->value, with_brace));
  res_expr = std::move(tmp);
  return RC::SUCCESS;
}
