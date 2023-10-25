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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
  if (nullptr != orderby_stmt_) {
    delete orderby_stmt_;
    orderby_stmt_ = nullptr;
  }
  project_exprs_.clear();
}

//static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
//{
//  const TableMeta &table_meta = table->table_meta();
//  const int field_num = table_meta.field_num();
//  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
//    field_metas.push_back(Field(table, table_meta.field(i)));
//  }
//}


static void wildcard_fields(Table *table, std::vector<std::unique_ptr<Expression>> &project_exprs)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.extra_filed_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    project_exprs.emplace_back(new FieldExpr(table, table_meta.field(i)));
  }
}

static void wildcard_fields(Table *table, std::vector<std::unique_ptr<Expression>> &project_exprs,
                            std::unordered_map<Table *, std::string>& alias_map, bool with_table_name)  // select * form
{
  auto it = alias_map.find(table);
  std::string table_alias_name;
  if (it != alias_map.end()) {
    table_alias_name = it->second;
  }

  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.extra_filed_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    FieldExpr* field_expr = new FieldExpr(table, table_meta.field(i));
    project_exprs.emplace_back(field_expr);
    if (with_table_name) {
      field_expr->set_alias(table_alias_name + '.' + table_meta.field(i)->name());
    }
    else {
      field_expr->set_alias(table_meta.field(i)->name());
    }
  }
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  std::unordered_map<Table *, std::string> alias_map;
  assert(select_sql.relation_names.size() == select_sql.alias_names.size());
  for (size_t i = 0; i < select_sql.relation_names.size(); i++) {
    const char *table_name = select_sql.relation_names[i].c_str();
    const char *alias_name = select_sql.alias_names[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));

    if (strlen(alias_name) != 0) {
      if (table_map.count(std::string(alias_name)) != 0) {  // 表的别名和其他的表名重复
        return RC::SCHEMA_TABLE_EXIST;
      }
      table_map.insert(std::pair<std::string, Table *>(alias_name, table)); // 别名的表
      alias_map.insert(std::pair<Table *, std::string>(table, alias_name));
    }
  }

  // collect query fields in `select` statement
  std::vector<std::unique_ptr<Expression>> project_expres;
  for (int i = static_cast<int>(select_sql.project_exprs.size()) - 1; i >= 0; i--) {
    const ExprSqlNode* expr = select_sql.project_exprs[i];
    if (expr->type == ExprSqlNodeType::UNDEFINED) {
      LOG_ERROR("表达式转化错误！！！");
      return RC::SQL_SYNTAX;
    }

    if (expr->type == ExprSqlNodeType::UNARY && expr->unary_expr->is_attr) {  // 表达式是一元表达式，且是属性，执行原本的代码
      const RelAttrSqlNode &relation_attr = expr->unary_expr->attr; // 属性，relation_name.attribute_name

      if (common::is_blank(relation_attr.relation_name.c_str()) &&    // select * from t;
          0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
        bool with_table_name = (tables.size() > 1);
        for (Table *table : tables) {
          wildcard_fields(table, project_expres, alias_map, with_table_name);
        }
      }
      else if (!common::is_blank(relation_attr.relation_name.c_str())) {  // select t.* from t; 或者 select t.id from t;
        const char *table_name = relation_attr.relation_name.c_str();
        const char *field_name = relation_attr.attribute_name.c_str();
        if (0 == strcmp(table_name, "*")) { // select *.attr from t;
          if (0 != strcmp(field_name, "*")) {
            LOG_WARN("invalid field name while table is *. attr=%s", field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          for (Table *table : tables) {
            wildcard_fields(table, project_expres);
          }
        } else {
          auto iter = table_map.find(table_name);
          if (iter == table_map.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = iter->second;
          if (0 == strcmp(field_name, "*")) {       // select t.* from t;
            wildcard_fields(table, project_expres);
          } else {                                  // select t.id from t;
            const FieldMeta *field_meta = table->table_meta().field(field_name);
            if (nullptr == field_meta) {
              LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }
            FieldExpr* field_expr = new FieldExpr(table, field_meta);
            std::string table_alias_name; // 表的别名
            if (tables.size() > 1) {
              table_alias_name = std::string(table->name()) + '.' + std::string(field_meta->name());
            } else {
              table_alias_name = std::string(field_meta->name());
            }
            field_expr->set_alias(table_alias_name);
            project_expres.emplace_back(field_expr);
          }
        }
      } else {  // select id from t  id没有对应表名
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = tables[0];
        const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }
        project_expres.emplace_back(new FieldExpr(table, field_meta));
      }
    }
    else {  // select 复杂表达式 from t;
      std::unique_ptr<Expression> project_expr;
      RC rc = Expression::create_expression(expr, table_map, tables, project_expr);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      assert(project_expr != nullptr);
      project_expres.emplace_back(std::move(project_expr));
    }
  }

  for (auto& node: select_sql.project_exprs) {
    delete node;
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), project_expres.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statemen
  std::vector<ConditionSqlNode> sum_conditions = select_sql.inner_join_conditions;
  sum_conditions.insert(sum_conditions.end(), select_sql.conditions.begin(), select_sql.conditions.end());
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db,
      default_table,
      &table_map,
      sum_conditions.data(),
      static_cast<int>(select_sql.conditions.size() + select_sql.inner_join_conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }
  OrderByStmt *orderby_stmt = nullptr;
  if (!select_sql.order_by_cols.empty())
  {
    rc = OrderByStmt::create(db,
        default_table,
        &table_map,
        select_sql.order_by_cols.data(),
        static_cast<int>(select_sql.order_by_cols.size()),
        orderby_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct order by stmt");
      return rc;
    }
  }
  // create select stmt
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->project_exprs_ = std::move(project_expres);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->orderby_stmt_ = orderby_stmt;

  bool with_table_name = select_stmt->tables_.size() != 1;
  for (auto &expression: select_stmt->project_expres()) {
    std::string expr_str;
    Expression::gen_project_name(expression.get(), with_table_name, expr_str);
    select_stmt->project_name_.emplace_back(expr_str);
  }

  stmt = select_stmt;

  return RC::SUCCESS;
}
