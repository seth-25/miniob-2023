#include "binary_expression.h"
#include <limits>
#include "common/lang/typecast.h"
#include "common/lang/string.h"
using namespace std;


AttrType BinaryExpression::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }
  const AttrType left_type = left_->value_type();
  const AttrType right_type = right_->value_type();

  if (left_type == AttrType::INTS && right_type == AttrType::INTS &&
      op_ != ExprOp::DIV_OP) {
    return AttrType::INTS;
  }
  if (left_type == AttrType::DATES || left_type == AttrType::BOOLEANS || left_type == AttrType::UNDEFINED
      || right_type == AttrType::DATES || right_type == AttrType::BOOLEANS || right_type == AttrType::UNDEFINED) {
    LOG_WARN("没实现类型%s与类型%s的计算", left_type, right_type);
    return AttrType::UNDEFINED;
  }
  return AttrType::FLOATS;
}

RC BinaryExpression::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;
  const AttrType target_type = value_type();
  if (target_type == AttrType::UNDEFINED) {
    return RC::UNIMPLENMENT;
  }

  if (left_value.is_null()||right_value.is_null())
  {
    value.set_null();
    return rc;
  }

  const AttrType left_type = left_value.attr_type();
  const AttrType right_type = right_value.attr_type();
  assert(left_->value_type() == AttrType::INTS || left_->value_type() == AttrType::FLOATS || left_->value_type() == AttrType::CHARS);
  assert(right_->value_type() == AttrType::INTS || right_->value_type() != AttrType::FLOATS|| right_->value_type() != AttrType::CHARS);

  // 全部转成float
  float left_float, right_float;
  if (left_type != AttrType::FLOATS) {
    left_float = *(float *)common::type_cast_to[left_type][FLOATS](left_value.data());
  }
  else {
    left_float = left_value.get_float();
  }
  if (right_type != AttrType::FLOATS) {
    right_float = *(float *)common::type_cast_to[right_type][FLOATS](right_value.data());
  }
  else {
    right_float = right_value.get_float();
  }
  float ans = 0;
  switch (op_) {
    case ExprOp::ADD_OP: {
      ans = left_float + right_float;
    } break;
    case ExprOp::SUB_OP: {
      ans = left_float - right_float;
    } break;
    case ExprOp::MUL_OP: {
      ans = left_float * right_float;
    } break;
    case ExprOp::DIV_OP: {
      if (abs(right_float) < 1e-6) {
        value.set_null();
        return rc;
        LOG_WARN("0作为除数");
      }
      else {
        ans = left_float / right_float;
      }

    } break;
    case ExprOp::NEGATIVE_OP: break; // todo
  }

  switch (target_type) {
    case CHARS: {
      value.set_type(AttrType::CHARS);
      std::string str = common::double_to_str(ans);
      value.set_string(str.c_str(), (int)str.length());
    } break;
    case INTS: {
      value.set_type(AttrType::INTS);
      value.set_int((int)ans);
    } break;
    case FLOATS: {
      value.set_type(AttrType::FLOATS);
      value.set_float(ans);
    } break;
    case UNDEFINED:
    case DATES:
    case NULLS:
    case BOOLEANS: {
      return RC::UNIMPLENMENT;
    } break;
  }
  return rc;
}


RC BinaryExpression::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC BinaryExpression::try_get_value(Value &value) const
{
  LOG_WARN("没实现binary expression的try to get value");
  RC rc = RC::INTERNAL;
  return rc;
}

RC BinaryExpression::create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr,
    const std::unordered_map<std::string, TableUnit*> &table_map, const TableUnit* default_table)
{
  assert(expr->type == ExprSqlNodeType::BINARY);
  bool with_brace = expr->with_brace;
  std::unique_ptr<Expression> left_expr;
  std::unique_ptr<Expression> right_expr;
  RC rc = Expression::create_expression(expr->binary_expr->left, left_expr, table_map, default_table);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = Expression::create_expression(expr->binary_expr->right, right_expr, table_map, default_table);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  std::unique_ptr<BinaryExpression> binary_expr(new BinaryExpression(
      expr->binary_expr->op, std::move(left_expr), std::move(right_expr), with_brace, expr->binary_expr->is_minus));
  res_expr = std::move(binary_expr);
  //    res_expr = std::make_unique<BinaryExpression>(expr->binary_expr->op, std::move(left_expr), std::move(right_expr), with_brace, expr->binary_expr->is_minus);
  return RC::SUCCESS;
}

const char BinaryExpression::get_op_char() const
{
  switch (op_) {
    case ExprOp::ADD_OP:
      return '+';
    case ExprOp::SUB_OP:
      return '-';
    case ExprOp::MUL_OP:
      return '*';
    case ExprOp::DIV_OP:
      return '/';
    default:
      LOG_ERROR("unsupported op");
      break;
  }
  return '?';
}

