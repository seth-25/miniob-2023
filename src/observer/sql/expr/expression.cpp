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
#include "function_expression.h"
#include "aggregation_expression.h"
#include <regex>
using namespace std;


RC Expression::create_expression(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, std::unique_ptr<Expression> &res_expr)
{
  RC rc = RC::SUCCESS;
  if (expr->type == ExprSqlNodeType::UNARY) {
    UnaryExprSqlNode *unary_expr = expr->unary_expr;
    if (unary_expr->is_attr) {
      rc = FieldExpr::create_expression(expr, table_map, tables, res_expr);
    } else {
      rc = ValueExpr::create_expression(expr, table_map, tables, res_expr);
    }
  } else if (expr->type == ExprSqlNodeType::BINARY) {
    rc = BinaryExpression::create_expression(expr, table_map, tables, res_expr);
  }
  else if (expr->type == ExprSqlNodeType::FUNCTION) {
    rc = FuncExpression::create_expression(expr, table_map, tables, res_expr);
  }
  else if (expr->type == ExprSqlNodeType::AGGREGATION) {
    rc = AggrFuncExpr::create_expression(expr, table_map, tables, res_expr);
  }

  if (expr->alias_name.length() != 0) { // 表达式存在别名，如field或function
    res_expr->set_alias(expr->alias_name);
  }
  return rc;
}


void Expression::gen_project_name(const Expression *expr, bool with_table_name, std::string &result_name)
{
  if (expr->get_alias().length() > 0) {
    result_name = expr->get_alias();
    return;
  }

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
    } break;
    case ExprType::BINARY: {
      BinaryExpression *binary_expr = (BinaryExpression *)expr;
      if (binary_expr->is_minus()) {
        result_name += '-';
      } else {
        gen_project_name(binary_expr->left().get(), with_table_name, result_name);
        result_name += binary_expr->get_op_char();
      }
      gen_project_name(binary_expr->right().get(), with_table_name, result_name);
    } break;
    case ExprType::FUNCTION: {
      FuncExpression *func_expr = (FuncExpression *)expr;
      switch (func_expr->get_func_type()) {
        case FuncType::FUNC_LENGTH: {
          result_name += "length(";
          gen_project_name(func_expr->left().get(), with_table_name, result_name);
          result_name += ")";
          break;
        }
        case FuncType::FUNC_ROUND: {
          result_name += "round(";
          if (func_expr->right() != nullptr) {
            gen_project_name(func_expr->left().get(), with_table_name, result_name);
            result_name += ",";
            gen_project_name(func_expr->right().get(), with_table_name, result_name);
          } else {
            gen_project_name(func_expr->left().get(), with_table_name, result_name);
          }
          result_name += ")";
          break;
        }
        case FuncType::FUNC_DATE_FORMAT: {
          result_name += "date_format(";
          gen_project_name(func_expr->left().get(), with_table_name, result_name);
          result_name += ",";
          gen_project_name(func_expr->right().get(), with_table_name, result_name);
          result_name += ")";
          break;
        }
        default:
          break;
      }
    } break;
    case ExprType::AGGRFUNC : {
      AggrFuncExpr *aggr_expr = (AggrFuncExpr *)expr;
      result_name += aggr_expr->get_func_name();
      result_name += '(';
      if (aggr_expr->is_param_value()) {
        gen_project_name(aggr_expr->value_expr().get(), with_table_name, result_name);

      } else {
        const Field &field = aggr_expr->field();
        if (!with_table_name) {
          result_name += std::string(field.table_name()) + '.' + std::string(field.field_name());
        } else {
          result_name += std::string(field.field_name());
        }
      }
      result_name += ')';
      break;
    }
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
//       const AggrFuncExpr *aggrfunc_expr = (const AggrFuncExpr *)expr;
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
RC FieldExpr::get_field_isnull_from_exprs(const Expression* expr, bool &nullable)
{
  switch (expr->type()) {
    case ExprType::FIELD: {
      const FieldExpr* field_expr = (const FieldExpr *)(expr);
      nullable &= field_expr->field().meta()->nullable();
      break;
    }
    case ExprType::AGGRFUNC: {
      nullable = false;
      //       const AggrFuncExpr *aggrfunc_expr = (const AggrFuncExpr *)expr;
      //       get_field_from_exprs(aggrfunc_expr->field_expr, fields);
      break;
    }
    case ExprType::BINARY: {
      BinaryExpression* binary_expr = (BinaryExpression*) expr;
      get_field_isnull_from_exprs(binary_expr->left().get(), nullable);
      get_field_isnull_from_exprs(binary_expr->right().get(), nullable);
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
RC FieldExpr::create_expression(const ExprSqlNode *expr, const unordered_map<std::string, Table *> &table_map,
    const vector<Table *> &tables, unique_ptr<Expression> &res_expr)
{
  assert(expr->type == ExprSqlNodeType::UNARY);
  bool with_brace = expr->with_brace;
  UnaryExprSqlNode *unary_expr = expr->unary_expr;
  assert(unary_expr->is_attr == true);

  const char *table_name = unary_expr->attr.relation_name.c_str();
  const char *field_name = unary_expr->attr.attribute_name.c_str();
  if (common::is_blank(table_name)) {   // select id from t  id没有对应表名
    if (tables.size() != 1) {
      LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    Table *table = tables[0];
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    std::unique_ptr<FieldExpr> field_expr(new FieldExpr(table, field_meta, with_brace));
    res_expr = std::move(field_expr);
  }
  else {  // select t.id from t
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
    std::unique_ptr<FieldExpr> field_expr(new FieldExpr(table, field_meta, with_brace));
    if (std::string(table_name) != std::string(table->name())) {  // 表存在别名
      if (tables.size() > 1) {
        field_expr->set_alias(std::string(table_name) + "." + std::string(field_name));
      }
    }
    res_expr = std::move(field_expr);
  }

  return RC::SUCCESS;
}

