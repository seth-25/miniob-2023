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
  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      op_ != ExprOp::DIV_OP) {
    return AttrType::INTS;
  }
  if (left_->value_type() == AttrType::DATES || left_->value_type() == AttrType::BOOLEANS || left_->value_type() == AttrType::UNDEFINED
      || right_->value_type() == AttrType::DATES || right_->value_type() == AttrType::BOOLEANS || right_->value_type() == AttrType::UNDEFINED) {
    LOG_WARN("没实现类型%s与类型%s的计算", left_->value_type(), right_->value_type());
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
  float ans;
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
        // todo NULL
        LOG_WARN("0作为除数");
        ans = numeric_limits<float>::max();
//        return RC::UNIMPLENMENT;
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