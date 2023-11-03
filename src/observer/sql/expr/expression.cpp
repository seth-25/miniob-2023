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
#include "subquery_expression.h"
#include "valuelist_expression.h"
using namespace std;

RC Expression::create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr,
    const std::unordered_map<std::string, TableUnit*> &table_map, const TableUnit* default_table, CompOp comp, Db *db,
    Trx *trx)
{
  RC rc = RC::SUCCESS;
  if (expr->type == ExprSqlNodeType::UNARY) {
    UnaryExprSqlNode *unary_expr = expr->unary_expr;
    if (unary_expr->is_attr) {
      rc = FieldExpr::create_expression(expr, res_expr, table_map, default_table);
    } else {
      rc = ValueExpr::create_expression(expr, res_expr);
    }
  } else if (expr->type == ExprSqlNodeType::BINARY) {
    rc = BinaryExpression::create_expression(expr, res_expr, table_map, default_table);
  }
  else if (expr->type == ExprSqlNodeType::FUNCTION) {
    rc = FuncExpression::create_expression(expr, res_expr, table_map, default_table);
  }
  else if (expr->type == ExprSqlNodeType::AGGREGATION) {
    rc = AggrFuncExpr::create_expression(expr, res_expr, table_map, default_table);
  }
  else if (expr->type == ExprSqlNodeType::SUBQUERY) {
    return SubQueryExpr::create_expression(expr, res_expr, table_map, comp, db, trx);
  }
  else if (expr->type == ExprSqlNodeType::VALUELIST) {
    return ValueListExpr::create_expression(expr, res_expr);
  }
  if (rc != RC::SUCCESS) {
    return rc;
  }
  if (expr->alias_name.length() != 0) { // 表达式存在别名，如field或function
    res_expr->set_alias(expr->alias_name);
  }
  return rc;
}

// 获取所有不在aggr内的field
RC Expression::get_field_exprs(const ExprSqlNode *expr, std::vector<std::unique_ptr<Expression>> &field_exprs,
    const std::unordered_map<std::string, TableUnit *> &table_map, const TableUnit *default_table)
{
  RC rc = RC::SUCCESS;
  if (expr->type == ExprSqlNodeType::UNARY) {
    UnaryExprSqlNode *unary_expr = expr->unary_expr;
    if (unary_expr->is_attr) {
      std::unique_ptr<Expression> field_expr;
      rc = FieldExpr::create_expression(expr, field_expr, table_map, default_table);
      field_exprs.emplace_back(std::move(field_expr));
    }
  }
  else if (expr->type == ExprSqlNodeType::BINARY) {
    rc = get_field_exprs(expr->binary_expr->left, field_exprs, table_map, default_table);
    if (rc != RC::SUCCESS) { return rc; }
    rc = get_field_exprs(expr->binary_expr->right, field_exprs, table_map, default_table);
  }
  return rc;
}

// 获取所有不在aggr内的field
RC Expression::get_field_exprs_from_project(const Expression* expr, std::vector<std::unique_ptr<Expression>> &field_exprs)
{
  RC rc = RC::SUCCESS;
  if (expr->type() == ExprType::FIELD) {  // todo unique改share，不再copy
    FieldExpr* field_expr = (FieldExpr*) expr;
    if (field_expr->is_table()) {
      std::unique_ptr<Expression> field_expr_copy(new FieldExpr(field_expr->field()));
      field_exprs.emplace_back(std::move(field_expr_copy));
    }
    else {
      std::shared_ptr<Expression> view_expr = field_expr->view_expr();
      string view_name = field_expr->table_name();
      std::unique_ptr<Expression> field_expr_copy(new FieldExpr(view_expr, view_name));
      field_exprs.emplace_back(std::move(field_expr_copy));
    }
  }
  else if (expr->type() == ExprType::BINARY) {
    BinaryExpression* binary_expr = (BinaryExpression*) expr;
    rc = get_field_exprs_from_project(binary_expr->left().get(), field_exprs);
    if (rc != RC::SUCCESS) { return rc; }
    rc = get_field_exprs_from_project(binary_expr->right().get(), field_exprs);
    if (rc != RC::SUCCESS) { return rc; }
  }
  return rc;
}

// 获取所有AggrFuncExpr
RC Expression::get_aggr_exprs(const ExprSqlNode *expr, std::vector<std::unique_ptr<Expression>> &aggr_exprs,
    const std::unordered_map<std::string, TableUnit *> &table_map, const TableUnit *default_table)
{
  RC rc = RC::SUCCESS;
  if (expr->type == ExprSqlNodeType::AGGREGATION) {
    std::unique_ptr<Expression> aggr_expr;
    AggrFuncExpr::create_expression(expr, aggr_expr, table_map, default_table);
    aggr_exprs.emplace_back(std::move(aggr_expr));
  }
  else if (expr->type == ExprSqlNodeType::BINARY) {

    rc = get_aggr_exprs(expr->binary_expr->left, aggr_exprs, table_map, default_table);
    if (rc != RC::SUCCESS) { return rc; }
    rc = get_aggr_exprs(expr->binary_expr->right, aggr_exprs, table_map, default_table);
  }
  return rc;
}


void Expression::gen_project_name(const Expression *expr, bool with_table_name, std::string &result_name, bool use_alias)
{
  if (expr->get_alias().length() > 0 && use_alias) {
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
      result_name += aggr_expr->to_string(with_table_name);
    } break;
    default:
      break;
  }
  if (expr->with_brace()) {
    result_name += ')';
  }
}
RC Expression::find_expr(vector<std::shared_ptr<Expression>> &exprs, shared_ptr<Expression> &res_expr, const std::string& find_expr_name, bool with_table_name)
{
  for (auto&expr : exprs) {
    string expr_name;
    if (!expr->get_alias().empty()) {
      expr_name = expr->get_alias();
    }
    else {
      if (expr->type() == ExprType::VALUE) {
        expr_name = ((ValueExpr *)expr.get())->to_string();
      }
      else if (expr->type() == ExprType::FIELD) {
        expr_name = ((FieldExpr *)expr.get())->to_string(with_table_name);
      }
      else if (expr->type() == ExprType::AGGRFUNC) {
        expr_name = ((AggrFuncExpr *)expr.get())->to_string(with_table_name);
      }
      else return RC::UNIMPLENMENT;  // 其他表达式类型，没别名的话暂不支持view查询
    }
    if (find_expr_name == expr_name) {
      res_expr = expr;
      return RC::SUCCESS;
    }
  }
  return RC::NOTFOUND;
}

/////////////////////////////////////////////////////////////////////////////////

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  if (is_table()) {
    unique_ptr<FieldExpr> field_expr_copy = make_unique<FieldExpr>(field_);
    return tuple.find_cell(TupleCellSpec(std::move(field_expr_copy)), value); // row tuple
  }
  else {
    std::unique_ptr<FieldExpr> field_expr_copy = std::make_unique<FieldExpr>(view_expr_, view_name_);
    return tuple.find_cell(TupleCellSpec(std::move(field_expr_copy)), value); // project tuple
  }
}

RC FieldExpr::get_field_expr_from_exprs(const Expression* expr, std::vector<FieldExpr*> &field_exprs)
{
  switch (expr->type()) {
    case ExprType::FIELD: {
      FieldExpr* field_expr = (FieldExpr *)(expr);
      field_exprs.emplace_back(field_expr);
      break;
    }
    case ExprType::AGGRFUNC: {
      AggrFuncExpr *aggr_expr = (AggrFuncExpr *)expr;
      FieldExpr* field_expr = (FieldExpr *)(aggr_expr->field_expr().get());
      field_exprs.emplace_back(field_expr);
      break;
    }
    case ExprType::BINARY: {
      BinaryExpression* binary_expr = (BinaryExpression*) expr;
      get_field_expr_from_exprs(binary_expr->left().get(), field_exprs);
      get_field_expr_from_exprs(binary_expr->right().get(), field_exprs);
      break;
    }
    default:
      break;
  }
  return RC::SUCCESS;
}
//RC FieldExpr::get_field_from_exprs(const Expression* expr, std::vector<Field> &fields)
//{
//  switch (expr->type()) {
//    case ExprType::FIELD: {
//      const FieldExpr* field_expr = (const FieldExpr *)(expr);
//      const Field &field = field_expr->field();
//      fields.emplace_back(field);
//      break;
//    }
//    case ExprType::AGGRFUNC: {
//      AggrFuncExpr *aggr_expr = (AggrFuncExpr *)expr;
//      fields.emplace_back(aggr_expr->field());
//      break;
//    }
//    case ExprType::BINARY: {
//      BinaryExpression* binary_expr = (BinaryExpression*) expr;
//      get_field_from_exprs(binary_expr->left().get(), fields);
//      get_field_from_exprs(binary_expr->right().get(), fields);
//      break;
//    }
//    default:
//      break;
//  }
//  return RC::SUCCESS;
//}

RC FieldExpr::get_field_isnull_from_exprs(const Expression* expr, bool &nullable)
{
  switch (expr->type()) {
    case ExprType::FIELD: {
      const FieldExpr* field_expr = (const FieldExpr *)(expr);
      if (!field_expr->is_table()) {  // 不支持查询view的字段是否是null
        return RC::UNIMPLENMENT;
      }
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
  if (is_table_) {
    const Field &field = field_;
    if (with_table_name) {
      str += std::string(field.table_name()) + '.' + std::string(field.field_name());
    } else {
      str += std::string(field.field_name());
    }
  }
  else {
    if (with_table_name) {
      str += std::string(view_name_) + '.' + std::string(view_field_name_);
    } else {
      str += std::string(view_field_name_);
    }
  }

  return str;
}


RC FieldExpr::create_expression(const ExprSqlNode *expr, unique_ptr<Expression> &res_expr,
    const unordered_map<std::string, TableUnit*> &table_map, const TableUnit* default_table)
{
  assert(expr->type == ExprSqlNodeType::UNARY);
  bool with_brace = expr->with_brace;
  UnaryExprSqlNode *unary_expr = expr->unary_expr;
  assert(unary_expr->is_attr == true);

  const char *table_name = unary_expr->attr.relation_name.c_str();
  const char *field_name = unary_expr->attr.attribute_name.c_str();
  if (common::is_blank(table_name)) {   // select id from t  id没有对应表名
    if (default_table == nullptr) { // 多表的情况
      LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    if (default_table->is_table()) {
      const Table* table = default_table->table();
      const FieldMeta *field_meta = table->table_meta().field(field_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
      std::unique_ptr<FieldExpr> field_expr(new FieldExpr(table, field_meta, with_brace));
      res_expr = std::move(field_expr);
    }
    else {
      SelectStmt* view_stmt = default_table->view_stmt();
      shared_ptr<Expression> view_expr;
      RC rc = Expression::find_expr(view_stmt->project_expres(), view_expr, field_name, false);
      if (rc != RC::SUCCESS) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      std::unique_ptr<FieldExpr> field_expr(new FieldExpr(view_expr, default_table->view_name()));
      res_expr = std::move(field_expr);
    }
  }
  else {  // 存在表名t， select t.id from t
    auto iter = table_map.find(table_name); // table_name 可能是 view
    if (iter == table_map.end()) {
      LOG_WARN("no such table in from list: %s", table_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    TableUnit* table_unit = iter->second;
    if (table_unit->is_table()) {
      const Table *table = table_unit->table();
      const FieldMeta *field_meta = table->table_meta().field(field_name);
      if (nullptr == field_meta) {  // 表达式里的field不支持select t.* from t;
        LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
      std::unique_ptr<FieldExpr> field_expr(new FieldExpr(table, field_meta, with_brace));
      if (std::string(table_name) != std::string(table->name())) {  // 表存在别名
        if (default_table == nullptr) { // 多表的情况
          field_expr->set_alias(std::string(table_name) + "." + std::string(field_name));
        }
      }
      res_expr = std::move(field_expr);
    }
    else {
      SelectStmt* view_stmt = table_unit->view_stmt();
      shared_ptr<Expression> view_expr;
      RC rc = Expression::find_expr(view_stmt->project_expres(), view_expr, field_name, false);
      if (rc != RC::SUCCESS) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      std::unique_ptr<FieldExpr> field_expr(new FieldExpr(view_expr, table_unit->view_name()));
      res_expr = std::move(field_expr);
    }
  }

  return RC::SUCCESS;
}

/*
RC FieldExpr::create_expression(const ExprSqlNode *expr, unique_ptr<Expression> &res_expr,
    const unordered_map<std::string, Table *> &table_map, const Table *default_table)
{
  assert(expr->type == ExprSqlNodeType::UNARY);
  bool with_brace = expr->with_brace;
  UnaryExprSqlNode *unary_expr = expr->unary_expr;
  assert(unary_expr->is_attr == true);

  const char *table_name = unary_expr->attr.relation_name.c_str();
  const char *field_name = unary_expr->attr.attribute_name.c_str();
  if (common::is_blank(table_name)) {   // select id from t  id没有对应表名
    if (!default_table) { // 多表的情况
      LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    const FieldMeta *field_meta = default_table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s", default_table->name(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    std::unique_ptr<FieldExpr> field_expr(new FieldExpr(default_table, field_meta, with_brace));
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
      if (!default_table) { // 多表的情况
        field_expr->set_alias(std::string(table_name) + "." + std::string(field_name));
      }
    }
    res_expr = std::move(field_expr);
  }

  return RC::SUCCESS;
}*/

