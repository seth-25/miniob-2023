/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "common/lang/string.h"
#include "value_expression.h"
#include "binary_expression.h"
#include <regex>
using namespace std;


RC Expression::create_expression(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, std::unique_ptr<Expression> &res_expr)
{
  bool with_brace = expr->with_brace;
  if (expr->type == ExprSqlNodeType::UNARY) {
    UnaryExprSqlNode *unary_expr = expr->unary_expr;
    if (unary_expr->is_attr) {
      const char *table_name = unary_expr->attr.relation_name.c_str();
      const char *field_name = unary_expr->attr.attribute_name.c_str();
      if (common::is_blank(table_name)) {
        if (tables.size() != 1) { // select id from t  id没有对应表名
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        Table *table = tables[0];
        const FieldMeta *field_meta = table->table_meta().field(field_name);
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        std::unique_ptr<FieldExpr> tmp(new FieldExpr(table, field_meta, with_brace));
        res_expr = std::move(tmp);
//        res_expr = std::make_unique<FieldExpr>(table, field_meta, with_brace);
        return RC::SUCCESS;
      } else {  // select t.id from t
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        const FieldMeta *field_meta = table->table_meta().field(field_name);
        if (nullptr == field_meta) {  // 不支持select t.* from t;
          LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        std::unique_ptr<FieldExpr> tmp(new FieldExpr(table, field_meta, with_brace));
        res_expr = std::move(tmp);
//        res_expr = std::make_unique<FieldExpr>(table, field_meta, with_brace);
        return RC::SUCCESS;
      }
    } else {
      std::unique_ptr<ValueExpr> tmp(new ValueExpr(unary_expr->value, with_brace));
      res_expr = std::move(tmp);
//      res_expr = std::make_unique<ValueExpr>(unary_expr->value, with_brace);
      return RC::SUCCESS;
    }
  } else if (expr->type == ExprSqlNodeType::BINARY) {
    std::unique_ptr<Expression> left_expr;
    std::unique_ptr<Expression> right_expr;
    RC rc = create_expression(expr->binary_expr->left, table_map, tables, left_expr);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    rc = create_expression(expr->binary_expr->right, table_map, tables, right_expr);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    std::unique_ptr<BinaryExpression> tmp(new BinaryExpression(
        expr->binary_expr->op, std::move(left_expr), std::move(right_expr), with_brace, expr->binary_expr->is_minus));
    res_expr = std::move(tmp);
//    res_expr = std::make_unique<BinaryExpression>(expr->binary_expr->op, std::move(left_expr), std::move(right_expr), with_brace, expr->binary_expr->is_minus);
    return RC::SUCCESS;
  }
//  else if (expr->type == FUNC) {
//    Expression *param_expr1;
//    Expression *param_expr2;
//    switch (expr->fexp->type) {
//      case FUNC_LENGTH: {
//        RC rc = create_expression(expr->fexp->params[0], table_map, tables, param_expr1);
//        if (rc != RC::SUCCESS) {
//          return rc;
//        }
//        // res_expr = new FuncExpression(expr->fexp->type, expr->fexp->param_size, param_expr1, param_expr2,
//        // with_brace);
//        break;
//      }
//      case FUNC_ROUND: {
//        RC rc = create_expression(expr->fexp->params[0], table_map, tables, param_expr1);
//        if (rc != RC::SUCCESS) {
//          return rc;
//        }
//        if (expr->fexp->param_size == 2) {
//          rc = create_expression(expr->fexp->params[1], table_map, tables, param_expr2);
//          if (rc != RC::SUCCESS) {
//            return rc;
//          }
//        }
//        // res_expr = new FuncExpression(expr->fexp->type, expr->fexp->param_size, param_expr1, param_expr2,
//        // with_brace);
//        break;
//      }
//      case FUNC_DATE_FORMAT: {
//        RC rc = create_expression(expr->fexp->params[0], table_map, tables, param_expr1);
//        if (rc != RC::SUCCESS) {
//          return rc;
//        }
//        rc = create_expression(expr->fexp->params[1], table_map, tables, param_expr2);
//        if (rc != RC::SUCCESS) {
//          return rc;
//        }
//        // res_expr = new FuncExpression(expr->fexp->type, expr->fexp->param_size, param_expr1, param_expr2,
//        // with_brace);
//        break;
//      }
//      default:
//        break;
//    }
//  }
//  else if (AGGRFUNC == expr->type) {
//    // TODO(wbj)
//    if (UNARY == expr->afexp->param->type && 0 == expr->afexp->param->uexp->is_attr) {
//      // count(*) count(1) count(Value)
//      assert(AggrFuncType::COUNT == expr->afexp->type);
//      // substitue * or 1 with some field
//      Expression *tmp_value_exp = nullptr;
//      RC rc = create_expression(expr->afexp->param, table_map, tables, tmp_value_exp);
//      if (rc != RC::SUCCESS) {
//        return rc;
//      }
//      assert(ExprType::VALUE == tmp_value_exp->type());
//      auto aggr_func_expr = new AggrFuncExpression(
//          AggrFuncType::COUNT, new FieldExpr(tables[0], tables[0]->table_meta().field(1)), with_brace);
//      aggr_func_expr->set_param_value((ValueExpr *)tmp_value_exp);
//      res_expr = aggr_func_expr;
//      return RC::SUCCESS;
//    }
//    Expression *param = nullptr;
//    RC rc = create_expression(expr->afexp->param, table_map, tables, param);
//    if (rc != RC::SUCCESS) {
//      return rc;
//    }
//    assert(nullptr != param && ExprType::FIELD == param->type());
//    res_expr = new AggrFuncExpression(expr->afexp->type, (FieldExpr *)param, with_brace);
//    return RC::SUCCESS;
//  }
  return RC::SUCCESS;
}


void Expression::gen_project_name(const Expression *expr, bool with_table_name, std::string &result_name)
{
  if (expr->with_brace()) {
    result_name += '(';
  }
  switch (expr->type()) {
    case ExprType::FIELD: {
      FieldExpr *field_expr = (FieldExpr *)expr;
      result_name += field_expr->to_string(with_table_name);
      break;
    }
    case ExprType::VALUE: {
      ValueExpr *value_expr = (ValueExpr *)expr;
      result_name += value_expr->to_string();
      break;
    }
    case ExprType::BINARY: {
      BinaryExpression *binary_expr = (BinaryExpression *)expr;
      if (binary_expr->is_minus()) {
        result_name += '-';
      } else {
        gen_project_name(binary_expr->left().get(), with_table_name, result_name);
        result_name += binary_expr->get_op_char();
      }
      gen_project_name(binary_expr->right().get(), with_table_name, result_name);
      break;
    }
      //    case ExprType::AGGRFUNCTION: {
      //      AggrFuncExpression *afexpr = (AggrFuncExpression *)expr;
      //      result_name += afexpr->get_func_name();
      //      result_name += '(';
      //      if (afexpr->is_param_value()) {
      //        gen_project_name(afexpr->get_param_value(), with_table_name, result_name);
      //
      //      } else {
      //        const Field &field = afexpr->field();
      //        if (!with_table_name) {
      //          result_name += std::string(field.table_name()) + '.' + std::string(field.field_name());
      //        } else {
      //          result_name += std::string(field.field_name());
      //        }
      //      }
      //      result_name += ')';
      //      break;
      //    }
    default:
      break;
  }
  if (expr->with_brace()) {
    result_name += ')';
  }
}

/////////////////////////////////////////////////////////////////////////////////

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  unique_ptr<FieldExpr> field_expr_copy = make_unique<FieldExpr>(field_);
  return tuple.find_cell(TupleCellSpec(std::move(field_expr_copy)), value);
}


RC FieldExpr::get_field_from_exprs(const Expression* expr, std::vector<Field> &fields)
{
  switch (expr->type()) {
    case ExprType::FIELD: {
      const FieldExpr* field_expr = (const FieldExpr *)(expr);
      const Field &field = field_expr->field();
      fields.emplace_back(field);
      break;
    }
    case ExprType::AGGRFUNC: {
//       const AggrFuncExpression *aggrfunc_expr = (const AggrFuncExpression *)expr;
//       get_field_from_exprs(aggrfunc_expr->field_expr, fields);
      break;
    }
    case ExprType::BINARY: {
      BinaryExpression* binary_expr = (BinaryExpression*) expr;
      get_field_from_exprs(binary_expr->left().get(), fields);
      get_field_from_exprs(binary_expr->right().get(), fields);
      break;
    }
    default:
      break;
  }
  return RC::SUCCESS;
}

std::string FieldExpr::to_string(bool with_table_name) const
{
  std::string str;
  const Field &field = field_;
  if (with_table_name) {
    str += std::string(field.table_name()) + '.' + std::string(field.field_name());
  } else {
    str += std::string(field.field_name());
  }
  return str;
}
/////////////////////////////////////////////////////////////////////////////////
//RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
//{
//  value = value_;
//  return RC::SUCCESS;
//}

/////////////////////////////////////////////////////////////////////////////////
//CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type)
//    : child_(std::move(child)), cast_type_(cast_type)
//{}

//CastExpr::~CastExpr()
//{}
//
//RC CastExpr::cast(const Value &value, Value &cast_value) const
//{
//  RC rc = RC::SUCCESS;
//  if (this->value_type() == value.attr_type()) {
//    cast_value = value;
//    return rc;
//  }
//
//  switch (cast_type_) {
//    case BOOLEANS: {
//      bool val = value.get_boolean();
//      cast_value.set_boolean(val);
//    } break;
//    default: {
//      rc = RC::INTERNAL;
//      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
//    }
//  }
//  return rc;
//}
//
//RC CastExpr::get_value(const Tuple &tuple, Value &cell) const
//{
//  RC rc = child_->get_value(tuple, cell);
//  if (rc != RC::SUCCESS) {
//    return rc;
//  }
//
//  return cast(cell, cell);
//}
//
//RC CastExpr::try_get_value(Value &value) const
//{
//  RC rc = child_->try_get_value(value);
//  if (rc != RC::SUCCESS) {
//    return rc;
//  }
//
//  return cast(value, value);
//}

////////////////////////////////////////////////////////////////////////////////

//ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
//    : comp_(comp), left_(std::move(left)), right_(std::move(right))
//{}
//
//ComparisonExpr::~ComparisonExpr()
//{}
//static void replace_all(std::string &str, const std::string &from, const std::string &to)
//{
//  if (from.empty()) {
//    return;
//  }
//  size_t pos = 0;
//  while (std::string::npos != (pos = str.find(from, pos))) {
//    str.replace(pos, from.length(), to);
//    pos += to.length();  // in case 'to' contains 'from'
//  }
//}
//RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
//{
//  RC rc = RC::SUCCESS;
//  result = false;
//  if (LIKE_OP == comp_ || NOT_LIKE_OP == comp_) {
//    assert(CHARS == left.attr_type() && CHARS == right.attr_type());
//    std::string raw_reg((const char *)right.get_string().c_str());
//    replace_all(raw_reg, "_", "[^']");
//    replace_all(raw_reg, "%", "[^']*");
//    std::regex reg(raw_reg.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
//    bool res = std::regex_match((const char *)left.get_string().c_str(), reg);
//    if ((LIKE_OP == comp_ && res ) || (NOT_LIKE_OP == comp_ && !res) ) {
//      result = true;
//    }
//    return rc;
//  }
//  int cmp_result = left.compare(right);
//  switch (comp_) {
//    case EQUAL_TO: {
//      result = (0 == cmp_result);
//    } break;
//    case LESS_EQUAL: {
//      result = (cmp_result <= 0);
//    } break;
//    case NOT_EQUAL: {
//      result = (cmp_result != 0);
//    } break;
//    case LESS_THAN: {
//      result = (cmp_result < 0);
//    } break;
//    case GREAT_EQUAL: {
//      result = (cmp_result >= 0);
//    } break;
//    case GREAT_THAN: {
//      result = (cmp_result > 0);
//    } break;
//    default: {
//      LOG_WARN("unsupported comparison. %d", comp_);
//      rc = RC::INTERNAL;
//    } break;
//  }
//
//  return rc;
//}
//
//RC ComparisonExpr::try_get_value(Value &cell) const
//{
//  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
//    ValueExpr *left_value_expr = static_cast<ValueExpr *>(left_.get());
//    ValueExpr *right_value_expr = static_cast<ValueExpr *>(right_.get());
//    const Value &left_cell = left_value_expr->get_value();
//    const Value &right_cell = right_value_expr->get_value();
//
//    bool value = false;
//    RC rc = compare_value(left_cell, right_cell, value);
//    if (rc != RC::SUCCESS) {
//      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
//    } else {
//      cell.set_boolean(value);
//    }
//    return rc;
//  }
//
//  return RC::INVALID_ARGUMENT;
//}
//
//RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
//{
//  Value left_value;
//  Value right_value;
//
//  RC rc = left_->get_value(tuple, left_value);
//  if (rc != RC::SUCCESS) {
//    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
//    return rc;
//  }
//  rc = right_->get_value(tuple, right_value);
//  if (rc != RC::SUCCESS) {
//    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
//    return rc;
//  }
//
//  bool bool_value = false;
//  rc = compare_value(left_value, right_value, bool_value);
//  if (rc == RC::SUCCESS) {
//    value.set_boolean(bool_value);
//  }
//  return rc;
//}

////////////////////////////////////////////////////////////////////////////////
//ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
//    : conjunction_type_(type), children_(std::move(children))
//{}
//
//RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
//{
//  RC rc = RC::SUCCESS;
//  if (children_.empty()) {
//    value.set_boolean(true);
//    return rc;
//  }
//
//  Value tmp_value;
//  for (const unique_ptr<Expression> &expr : children_) {
//    rc = expr->get_value(tuple, tmp_value);
//    if (rc != RC::SUCCESS) {
//      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
//      return rc;
//    }
//    bool bool_value = tmp_value.get_boolean();
//    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
//      value.set_boolean(bool_value);
//      return rc;
//    }
//  }
//
//  bool default_value = (conjunction_type_ == Type::AND);
//  value.set_boolean(default_value);
//  return rc;
//}

////////////////////////////////////////////////////////////////////////////////
//
//ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
//    : arithmetic_type_(type), left_(left), right_(right)
//{}
//ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
//    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
//{}
//
//AttrType ArithmeticExpr::value_type() const
//{
//  if (!right_) {
//    return left_->value_type();
//  }
//
//  if (left_->value_type() == AttrType::INTS &&
//      right_->value_type() == AttrType::INTS &&
//      arithmetic_type_ != Type::DIV) {
//    return AttrType::INTS;
//  }
//
//  return AttrType::FLOATS;
//}
//
//RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
//{
//  RC rc = RC::SUCCESS;
//
//  const AttrType target_type = value_type();
//
//  switch (arithmetic_type_) {
//    case Type::ADD: {
//      if (target_type == AttrType::INTS) {
//        value.set_int(left_value.get_int() + right_value.get_int());
//      } else {
//        value.set_float(left_value.get_float() + right_value.get_float());
//      }
//    } break;
//
//    case Type::SUB: {
//      if (target_type == AttrType::INTS) {
//        value.set_int(left_value.get_int() - right_value.get_int());
//      } else {
//        value.set_float(left_value.get_float() - right_value.get_float());
//      }
//    } break;
//
//    case Type::MUL: {
//      if (target_type == AttrType::INTS) {
//        value.set_int(left_value.get_int() * right_value.get_int());
//      } else {
//        value.set_float(left_value.get_float() * right_value.get_float());
//      }
//    } break;
//
//    case Type::DIV: {
//      if (target_type == AttrType::INTS) {
//        if (right_value.get_int() == 0) {
//          // NOTE: 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
//          value.set_int(numeric_limits<int>::max());
//        } else {
//          value.set_int(left_value.get_int() / right_value.get_int());
//        }
//      } else {
//        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
//          // NOTE: 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
//          value.set_float(numeric_limits<float>::max());
//        } else {
//          value.set_float(left_value.get_float() / right_value.get_float());
//        }
//      }
//    } break;
//
//    case Type::NEGATIVE: {
//      if (target_type == AttrType::INTS) {
//        value.set_int(-left_value.get_int());
//      } else {
//        value.set_float(-left_value.get_float());
//      }
//    } break;
//
//    default: {
//      rc = RC::INTERNAL;
//      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
//    } break;
//  }
//  return rc;
//}
//
//RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
//{
//  RC rc = RC::SUCCESS;
//
//  Value left_value;
//  Value right_value;
//
//  rc = left_->get_value(tuple, left_value);
//  if (rc != RC::SUCCESS) {
//    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
//    return rc;
//  }
//  rc = right_->get_value(tuple, right_value);
//  if (rc != RC::SUCCESS) {
//    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
//    return rc;
//  }
//  return calc_value(left_value, right_value, value);
//}
//
//RC ArithmeticExpr::try_get_value(Value &value) const
//{
//  RC rc = RC::SUCCESS;
//
//  Value left_value;
//  Value right_value;
//
//  rc = left_->try_get_value(left_value);
//  if (rc != RC::SUCCESS) {
//    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
//    return rc;
//  }
//
//  if (right_) {
//    rc = right_->try_get_value(right_value);
//    if (rc != RC::SUCCESS) {
//      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
//      return rc;
//    }
//  }
//
//  return calc_value(left_value, right_value, value);
//}