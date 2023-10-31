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

  if (nullptr != order_by_stmt_) {
    delete order_by_stmt_;
    order_by_stmt_ = nullptr;
  }

  if (nullptr != group_by_stmt_) {
    delete group_by_stmt_;
    group_by_stmt_ = nullptr;
  }

  if (nullptr != having_stmt_) {
    delete having_stmt_;
    having_stmt_ = nullptr;
  }

  if (nullptr != order_by_for_group_stmt_) {
    delete order_by_for_group_stmt_;
    order_by_for_group_stmt_ = nullptr;
  }

  project_exprs_.clear();
  project_name_.clear();
}

static void wildcard_fields(Table *table, std::vector<std::unique_ptr<Expression>> &project_exprs)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.extra_filed_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    project_exprs.emplace_back(new FieldExpr(table, table_meta.field(i)));
  }
}

static void wildcard_fields(Table *table, std::vector<std::unique_ptr<Expression>> &project_exprs,
                            const std::unordered_map<Table *, std::string>& alias_map, bool with_table_name)
{  // select * form，投影项是所有表，需要找到这些表对应存在的别名，并设置
  auto it = alias_map.find(table);
  std::string table_alias_name = table->name();
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

RC create_query_field(std::vector<std::unique_ptr<Expression>> &project_expres, const SelectSqlNode &select_sql, Db *db,
    const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map,
    const std::unordered_map<Table *, std::string> &alias_map)
{
  for (int i = static_cast<int>(select_sql.project_exprs.size()) - 1; i >= 0; i--) {
    const ExprSqlNode* expr = select_sql.project_exprs[i];
    if (expr->type == ExprSqlNodeType::UNDEFINED) {
      LOG_ERROR("表达式转化错误！！！");
      return RC::SQL_SYNTAX;
    }
    bool with_table_name = (tables.size() > 1);
    if (expr->type == ExprSqlNodeType::UNARY && expr->unary_expr->is_attr) {  // 表达式是一元表达式，且是属性，执行原本的代码
      const RelAttrSqlNode &relation_attr = expr->unary_expr->attr; // 属性，relation_name.attribute_name

      if (common::is_blank(relation_attr.relation_name.c_str()) &&    // select * from t;
          0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {

        for (Table *table : tables) {
          wildcard_fields(table, project_expres, alias_map, with_table_name);
        }
      }
      else if (!common::is_blank(relation_attr.relation_name.c_str())) {  // select t.* from t; 或者 select t.id from t;
        const char *table_name = relation_attr.relation_name.c_str();
        const char *field_name = relation_attr.attribute_name.c_str();
        if (0 == strcmp(table_name, "*")) {
          if (0 != strcmp(field_name, "*")) { // select *.attr from t;
            LOG_WARN("invalid field name while table is *. attr=%s", field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          for (Table *table : tables) { // select *.* from t;
            wildcard_fields(table, project_expres, alias_map, with_table_name);
          }
        }
        else {
          auto iter = table_map.find(table_name);
          if (iter == table_map.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = iter->second;
          if (0 == strcmp(field_name, "*")) {       // select t.* from t;
            wildcard_fields(table, project_expres, alias_map, with_table_name);
          }
          else {                                  // select t.id from t;
            const FieldMeta *field_meta = table->table_meta().field(field_name);
            if (nullptr == field_meta) {
              LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }
            FieldExpr* field_expr = new FieldExpr(table, field_meta);
            std::string alias_name = expr->alias_name; // 投影列的别名
            if (alias_name.empty()) {
              if (tables.size() > 1) {
                alias_name = std::string(table->name()) + '.' + std::string(field_meta->name());
              } else {
                alias_name = std::string(field_meta->name());
              }
            }
            field_expr->set_alias(alias_name);
            project_expres.emplace_back(field_expr);
          }
        }
      }
      else {  // select id from t  id没有对应表名
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
      if (rc != RC::SUCCESS) { return rc; }
      assert(project_expr != nullptr);
      project_expres.emplace_back(std::move(project_expr));
    }
  }
  return RC::SUCCESS;
}

RC SelectStmt::create(Db *db, Trx* trx, const SelectSqlNode &select_sql, const std::unordered_map<std::string, Table *>& parent_table_map, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // 1. collect tables in `from` statement，记录from后面的table
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


  // 2. collect query fields in `select` statement，将投影列转换成表达式
  std::vector<std::unique_ptr<Expression>> project_exprs;
  RC rc = create_query_field(project_exprs, select_sql, db, tables, table_map, alias_map);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), project_exprs.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  std::unordered_map<std::string, Table *> subquery_table_map = table_map;
  subquery_table_map.insert(parent_table_map.begin(), parent_table_map.end());  // 子查询可能有父表

  // 3. create filter statement in `where` statement，将where后面条件转化成filter_stmt
  std::vector<ConditionSqlNode> sum_conditions = select_sql.inner_join_conditions;
//  sum_conditions.insert(sum_conditions.end(), select_sql.conditions.begin(), select_sql.conditions.end());
  if (select_sql.condition.comp != NO_OP) { // 存在where条件
    sum_conditions.emplace_back(select_sql.condition);
  }
  FilterStmt *filter_stmt = nullptr;
  if (!sum_conditions.empty()) {
    rc = FilterStmt::create(db,
        trx,
        default_table,
        &subquery_table_map,
        sum_conditions.data(),
        static_cast<int>(sum_conditions.size()),
        filter_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
  }


  // 4. 创建order by statement
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


  // 5. 创建Having statement
  FilterStmt* having_stmt = nullptr;
  if (!select_sql.having_conditions.empty()) {
    rc = FilterStmt::create(db,
        trx,
        default_table,
        &table_map,
        select_sql.having_conditions.data(),
        static_cast<int>(select_sql.having_conditions.size()),
        having_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct having stmt");
      return rc;
    }
  }


  // 6. 创建group by statement，在group by oper里计算aggr，所以只要有aggr，不管是否有group by都需要创建
  std::vector<std::unique_ptr<Expression>> field_exprs;
  std::vector<std::unique_ptr<Expression>> aggr_exprs;
  int num_project_field = 0, num_project_aggr = 0;  // 用于记录哪些是投影的表达式，哪些是having的表达式
  for (auto& project_expr: select_sql.project_exprs) {  // 从投影中获取aggr
    rc = Expression::get_aggr_exprs(project_expr, table_map, tables, aggr_exprs);
    if (rc != RC::SUCCESS) { return rc; }
  }
  for (auto& project_expr: project_exprs) {  // 从投影中获取field，filed可能有*，用处理后的project_exprs获取
    rc = Expression::get_field_exprs(project_expr, table_map, tables, field_exprs);
    if (rc != RC::SUCCESS) { return rc; }
  }
  num_project_field = (int)field_exprs.size();
  num_project_aggr = (int)aggr_exprs.size();
  if (!select_sql.having_conditions.empty()) {
    for (auto& condition: select_sql.having_conditions) { // 从having条件中中获取field和aggr
      rc = Expression::get_field_exprs(condition.left, table_map, tables, field_exprs);
      if (rc != RC::SUCCESS) { return rc; }
      rc = Expression::get_field_exprs(condition.right, table_map, tables, field_exprs);
      if (rc != RC::SUCCESS) { return rc; }
      rc = Expression::get_aggr_exprs(condition.left, table_map, tables, aggr_exprs);
      if (rc != RC::SUCCESS) { return rc; }
      rc = Expression::get_aggr_exprs(condition.right, table_map, tables, aggr_exprs);
      if (rc != RC::SUCCESS) { return rc; }
    }
  }
  GroupByStmt* group_by_stmt = nullptr;
  if (!aggr_exprs.empty()) {
    rc = GroupByStmt::create(db,
        default_table,
        &table_map,
        select_sql.group_by_cols,
        aggr_exprs,
        field_exprs,
        num_project_aggr,
        num_project_field,
        group_by_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct group by stmt");
      return rc;
    }
  }


  // 7. 创建order by for group by statement
  OrderByStmt* order_by_for_group_stmt = nullptr;
  if (!select_sql.group_by_cols.empty()) {
    int group_by_num = (int)select_sql.group_by_cols.size();
    OrderBySqlNode order_by_for_group[group_by_num];
    for (int i = 0; i < group_by_num; i ++ ) {
      order_by_for_group[i].attribute = select_sql.group_by_cols[i];
      order_by_for_group[i].is_asc = true;
    }
    rc = OrderByStmt::create(
        db, default_table, &table_map, order_by_for_group, group_by_num, order_by_for_group_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct order by stmt for groupby");
      return rc;
    }
  }


  // 8. create select stmt
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->project_exprs_ = std::move(project_exprs);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->order_by_stmt_ = orderby_stmt;
  select_stmt->having_stmt_ = having_stmt;
  select_stmt->group_by_stmt_ = group_by_stmt;
  select_stmt->order_by_for_group_stmt_ = order_by_for_group_stmt;

  bool with_table_name = select_stmt->tables_.size() != 1;
  for (auto &expression: select_stmt->project_expres()) {
    std::string expr_str;
    Expression::gen_project_name(expression.get(), with_table_name, expr_str);
    select_stmt->project_name_.emplace_back(expr_str);
  }
  stmt = select_stmt;


  // todo 回收select_sql的各项表达式
  // todo SubQueryExpr需要delete SelectSqlNode
  for (auto& node: select_sql.project_exprs) {
    delete node;  // todo 递归删除
  }
  for (auto& node: select_sql.having_conditions) {
    delete node.left;  // todo 递归删除
    delete node.right;
  }
  for (auto& node: select_sql.inner_join_conditions) {
    delete node.left;  // todo 递归删除
    delete node.right;
  }
  if (select_sql.condition.comp != CompOp::NO_OP) {
    delete select_sql.condition.left;  // todo 递归删除
    delete select_sql.condition.right;
  }


  return RC::SUCCESS;
}
