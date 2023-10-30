#include "comparison_expression.h"
#include "value_expression.h"
#include "regex"
#include "subquery_expression.h"
#include "valuelist_expression.h"
using namespace std;

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr()
{}
static void replace_all(std::string &str, const std::string &from, const std::string &to)
{
  if (from.empty()) {
    return;
  }
  size_t pos = 0;
  while (std::string::npos != (pos = str.find(from, pos))) {
    str.replace(pos, from.length(), to);
    pos += to.length();  // in case 'to' contains 'from'
  }
}
RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC rc = RC::SUCCESS;
  result = false;
  if (CompOp::IS_NULL == comp_) {
    assert(right.is_null());
    result = left.is_null();
    return rc;
  }
  if (CompOp::IS_NOT_NULL == comp_) {
    assert(right.is_null());
    result = !left.is_null();
    return rc;
  }
  if (left.is_null() || right.is_null()) {
    result = false;
    return rc;
  }
  if (LIKE_OP == comp_ || NOT_LIKE_OP == comp_) {
    assert(CHARS == left.attr_type() && CHARS == right.attr_type() || TEXTS == left.attr_type() && CHARS == right.attr_type());
    std::string raw_reg((const char *)right.get_string().c_str());
    replace_all(raw_reg, "_", "[^']");
    replace_all(raw_reg, "%", "[^']*");
    std::regex reg(raw_reg.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
    bool res = std::regex_match((const char *)left.get_string().c_str(), reg);
    if ((LIKE_OP == comp_ && res ) || (NOT_LIKE_OP == comp_ && !res) ) {
      result = true;
    }
    return rc;
  }
  if (CompOp::EXISTS_OP == comp_ || CompOp::NOT_EXISTS_OP == comp_) {
    result = (CompOp::NOT_EXISTS_OP == comp_) ? left.is_null() : !left.is_null();
    return rc;
  }
  int cmp_result = left.compare(right);
  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *left_value_expr = static_cast<ValueExpr *>(left_.get());
    ValueExpr *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell = left_value_expr->get_value();
    const Value &right_cell = right_value_expr->get_value();

    bool value = false;
    RC rc = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}


bool check_in_values(const Value& value, const vector<Value>& values) {
  for (auto & v: values) {
    if (!value.is_null() && v == value) {
      return true;
    }
  }
  return false;
}

bool values_has_null(const vector<Value>& values) {
  for (auto &v: values) {
    if (v.is_null()) {
      return true;
    }
  }
  return false;
}

RC ComparisonExpr::compare_in(const Value& left_value, const Tuple &tuple, bool &result) const
{
  result = false;

  if (left_value.is_null()) { // null不在任何list里
    result = false;
    return RC::SUCCESS;
  }

  vector<Value> in_values = { Value() };
  if (right_->type() == ExprType::SUBSQUERY) {
    const SubQueryExpr* sub_query_expr = (const SubQueryExpr *)right_.get();
    RC rc = sub_query_expr->open_sub_query();
    if (rc != RC::SUCCESS) { return rc; }
    while (RC::SUCCESS == (rc = sub_query_expr->get_one_value(tuple, in_values.back()))) {
      in_values.emplace_back(Value());
    }
    in_values.pop_back(); // 去掉最后一个空的
    if (RC::RECORD_EOF != rc) {
      LOG_ERROR("[NOT] IN Get SubQuery Value Failed.");
      return rc;
    }
    sub_query_expr->close_sub_query();
  }
  else if (right_->type() == ExprType::VALUELIST){
    const ValueListExpr* list_expr = (const ValueListExpr *)right_.get();
    in_values = list_expr->get_values();
  }
  else {
    // in 右侧必须是子查询或value list
    return RC::SQL_SYNTAX;
  }
  if (CompOp::IN_OP == comp_) {
    result = check_in_values(left_value, in_values);
  }
  else {
    // not in 只要有null都是false
    result = !values_has_null(in_values) && !check_in_values(left_value, in_values);
  }
  return RC::SUCCESS;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  // 1. 计算左边的value
  Value left_value;
  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (comp_ == CompOp::IN_OP || comp_ == CompOp::NOT_IN_OP) { // in或not in右值是多个
    bool bool_value = false;
    rc = compare_in(left_value, tuple, bool_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare in. rc=%s", strrc(rc));
      return rc;
    }
    value.set_boolean(bool_value);
    return rc;
  }

  // 2.计算右边的value
  Value right_value;
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  // 3. 左右进行比较
  bool bool_value = false;
  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}