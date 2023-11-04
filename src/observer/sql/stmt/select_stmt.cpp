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
#include "sql/stmt/group_by_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/expr/value_expression.h"
#include "sql/expr/aggregation_expression.h"

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

static void wildcard_fields(TableUnit*table_unit, std::vector<std::shared_ptr<Expression>> &project_exprs,
                            const std::unordered_map<TableUnit*, std::string>& alias_map, bool with_table_name)
{  // select * form，投影项是所有表，需要找到这些表对应存在的别名，并设置
  if (table_unit->is_table()) {
    const Table* table = table_unit->table();

    auto it = alias_map.find(table_unit);
    std::string table_alias = table->name();
    if (it != alias_map.end()) {
      table_alias = it->second;
    }

    const TableMeta &table_meta = table->table_meta();
    const int field_num = table_meta.field_num() - table_meta.extra_filed_num();
    for (int i = table_meta.sys_field_num(); i < field_num; i++) {
      FieldExpr* field_expr = nullptr;
      if (table_alias != table->name()) {
        field_expr = new FieldExpr(table, table_alias, table_meta.field(i));
      }
      else {
        field_expr = new FieldExpr(table, "", table_meta.field(i));
      }

      if (with_table_name) {
        field_expr->set_alias(table_alias + '.' + table_meta.field(i)->name());
      }
      else {
        field_expr->set_alias(table_meta.field(i)->name());
      }
      project_exprs.emplace_back(field_expr);
    }
  }
  else {
    SelectStmt* view_stmt = table_unit->view_stmt();
    auto it = alias_map.find(table_unit);
    std::string view_alias_name = table_unit->view_name();
    if (it != alias_map.end()) {
      view_alias_name = it->second;
    }
    for (auto& expr: view_stmt->project_expres()) {
      std::shared_ptr<FieldExpr> field_expr(new FieldExpr(expr, table_unit->view_name()));
      // 子查询的投影列自己不会再有表名，如create view v as select t.id from t;
      // select v1.id from v as v1 合法； 不会有 select v1.t.id from v as v1;
      string view_expr_name = field_expr->to_string(false);
      if (with_table_name) {
        field_expr->set_alias(view_alias_name + '.' + view_expr_name);
      }
      else {
        field_expr->set_alias(view_expr_name);
      }
      project_exprs.emplace_back(field_expr);
    }
  }
}

static RC normal_field(TableUnit* table_unit, std::vector<std::shared_ptr<Expression>> &project_exprs, const char* field_name, const ExprSqlNode* expr) {
  FieldExpr* field_expr = nullptr;
  if (table_unit->is_table())
  {
    const Table *table = table_unit->table();
    string table_alias = table_unit->table_alias();
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta)
    {
      LOG_WARN("no such field. field=%s.%s",  table->name(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_expr = new FieldExpr(table, table_alias, field_meta);
  }
  else
  {
    SelectStmt* view_stmt = table_unit->view_stmt();
    shared_ptr<Expression> view_expr;
    RC rc = Expression::find_expr(view_stmt->project_expres(), view_expr, field_name, false);
    if (rc != RC::SUCCESS) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_expr = new FieldExpr(view_expr, table_unit->view_name());
  }
  assert(field_expr != nullptr);
  if (!expr->alias_name.empty()) {  // 投影列的别名
    field_expr->set_alias(expr->alias_name);
  }
  project_exprs.emplace_back(field_expr);
  return RC::SUCCESS;
}

RC create_query_field(std::vector<std::shared_ptr<Expression>> &project_exprs, const SelectSqlNode &select_sql, Db *db,
    const std::vector<TableUnit*> &tables, const std::unordered_map<std::string, TableUnit*> &table_map,
    const std::unordered_map<TableUnit* , std::string> &alias_map)
{
  for (int i = static_cast<int>(select_sql.project_exprs.size()) - 1; i >= 0; i--)
  {
      const ExprSqlNode* expr = select_sql.project_exprs[i];
      if (expr->type == ExprSqlNodeType::UNDEFINED) {
        LOG_ERROR("表达式转化错误！！！");
        return RC::SQL_SYNTAX;
      }
      bool with_table_name = (tables.size() > 1);
      if (expr->type == ExprSqlNodeType::UNARY && expr->unary_expr->is_attr)
      {  // 表达式是一元表达式，且是属性，执行原本的代码
          const RelAttrSqlNode &relation_attr = expr->unary_expr->attr; // 属性，relation_name.attribute_name
          const char *table_name = relation_attr.relation_name.c_str();
          const char *field_name = relation_attr.attribute_name.c_str();

          if (common::is_blank(table_name) && 0 == strcmp(field_name, "*"))   // 不存在表名，属性名是*，select * from t;
          {
              for (TableUnit* table_unit : tables) {
                  wildcard_fields(table_unit, project_exprs, alias_map, with_table_name);
              }
          }
          else if (!common::is_blank(relation_attr.relation_name.c_str()))
          {  // 存在表名，select *.id from t; select *.* from t; select t.* from t; select t.id from t;

              if (0 == strcmp(table_name, "*"))
              {
                  if (0 != strcmp(field_name, "*"))
                  { // select *.attr from t;
                      LOG_WARN("invalid field name while table is *. attr=%s", field_name);
                      return RC::SCHEMA_FIELD_MISSING;
                  }
                  for (TableUnit *table_unit : tables)
                  { // select *.* from t;
                      wildcard_fields(table_unit, project_exprs, alias_map, with_table_name);
                  }
              }
              else
              {
                  auto iter = table_map.find(table_name); // table_map包括别名的表，此处table_name可能是表别名
                  if (iter == table_map.end())
                  {
                      LOG_WARN("no such table_unit in from list: %s", table_name);
                      return RC::SCHEMA_FIELD_MISSING;
                  }
                  TableUnit *table_unit = iter->second;
                  if (0 == strcmp(field_name, "*")) // select t.* from t;
                  {
                      wildcard_fields(table_unit, project_exprs, alias_map, with_table_name);
                  }
                  else         // select t.id from t;
                  {
                      RC rc = normal_field(table_unit, project_exprs, field_name, expr);
                      if (rc != RC::SUCCESS) {
                        LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name);
                        return RC::SCHEMA_FIELD_MISSING;
                      }
                  }
              }
          }
          else {  // select id from t  id没有对应表名，用default table
              if (tables.size() != 1)
              {
                  LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name);
                  return RC::SCHEMA_FIELD_MISSING;
              }
              TableUnit *table_unit = tables[0];
              RC rc = normal_field(table_unit, project_exprs, field_name, expr);
              if (rc != RC::SUCCESS) {
                LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name);
                return RC::SCHEMA_FIELD_MISSING;
              }
          }
      }
      else {  // select 复杂表达式 from t;
          std::unique_ptr<Expression> project_expr;
          TableUnit* default_table = nullptr;
          if (tables.size() == 1) {
            default_table = tables[0];
          }
          RC rc = Expression::create_expression(expr, project_expr, table_map, default_table);
          if (rc != RC::SUCCESS) { return rc; }
          assert(project_expr != nullptr);
          project_exprs.emplace_back(std::move(project_expr));
      }
  }
  return RC::SUCCESS;
}

RC SelectStmt::init_view(const string& table_name, Db* db, Trx* trx, SelectStmt*& view_stmt) {
  auto view_it = ViewMapHelper::get_instance()->get().find(table_name);
  if (view_it == ViewMapHelper::get_instance()->get().end()) {  // 不存在view
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  SelectSqlNode &view_select = view_it->second;
  std::unordered_map<std::string, TableUnit*> empty_table_map;
  SelectStmt::create(db, trx, view_select, empty_table_map, (Stmt*&)view_stmt);
  // todo view_stmts用完后delete view_stmt和其表达式
  return RC::SUCCESS;
}

RC SelectStmt::create(Db *db, Trx* trx, const SelectSqlNode &select_sql, const unordered_map<string, TableUnit*>& parent_table_map, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // 1. collect tables in `from` statement，记录from后面的table
  vector<TableUnit*> tables;
  unordered_map<std::string, TableUnit*> table_map;
  unordered_map<TableUnit*, std::string> alias_map;

  assert(select_sql.relation_names.size() == select_sql.alias_names.size());
  for (size_t i = 0; i < select_sql.relation_names.size(); i++) {
    const char *table_name = select_sql.relation_names[i].c_str();
    const char *alias_name = select_sql.alias_names[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    TableUnit* table_unit = nullptr;
    if (nullptr == table) { // 找不到表，有可能是view
      SelectStmt* view_stmt = nullptr;
      if (RC::SUCCESS == SelectStmt::init_view(table_name, db, trx, view_stmt)) {  // 判断是否是view, 如果是则初始化view的条件
        table_unit = new TableUnit(view_stmt, table_name);
      }
      else {
        LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
    }
    else {
      table_unit = new TableUnit(table, alias_name);
    }

    assert(table_unit != nullptr);
    tables.emplace_back(table_unit);
    table_map.insert(std::pair<std::string, TableUnit*>(table_name, table_unit));

    if (strlen(alias_name) != 0) {
      if (table_map.count(std::string(alias_name)) != 0) {  // 表的别名和其他的表名重复
        return RC::SCHEMA_TABLE_EXIST;
      }
      table_map.insert(std::pair<std::string, TableUnit*>(alias_name, table_unit)); // 别名的表
      alias_map.insert(std::pair<TableUnit*, std::string>(table_unit, alias_name));
    }
  }

  TableUnit* default_table = nullptr; // empty table unit
  if (tables.size() == 1) {
    default_table = tables[0];
  }
  std::unordered_map<std::string, TableUnit*> subquery_table_map = table_map;
  subquery_table_map.insert(parent_table_map.begin(), parent_table_map.end());  // 子查询可能有父表



  // 2. collect query fields in `select` statement，将投影列转换成表达式
  std::vector<std::shared_ptr<Expression>> project_exprs;
  RC rc = create_query_field(project_exprs, select_sql, db, tables, table_map, alias_map);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), project_exprs.size());


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
    rc = Expression::get_aggr_exprs(project_expr, aggr_exprs, table_map, default_table);
    if (rc != RC::SUCCESS) { return rc; }
  }
  for (auto& project_expr: project_exprs) {  // 从投影中获取field，filed可能有*，用处理后的project_exprs获取
    rc = Expression::get_field_exprs_from_project(project_expr.get(), field_exprs);
    if (rc != RC::SUCCESS) { return rc; }
  }
  num_project_field = (int)field_exprs.size();
  num_project_aggr = (int)aggr_exprs.size();
  if (!select_sql.having_conditions.empty()) {
    for (auto& condition: select_sql.having_conditions) { // 从having条件中中获取field和aggr
      rc = Expression::get_field_exprs(condition.left, field_exprs, table_map, default_table);
      if (rc != RC::SUCCESS) { return rc; }
      rc = Expression::get_field_exprs(condition.right, field_exprs, table_map, default_table);
      if (rc != RC::SUCCESS) { return rc; }
      rc = Expression::get_aggr_exprs(condition.left, aggr_exprs, table_map, default_table);
      if (rc != RC::SUCCESS) { return rc; }
      rc = Expression::get_aggr_exprs(condition.right, aggr_exprs, table_map, default_table);
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
  // todo 内存中的view select不能在这删
//  for (auto& node: select_sql.project_exprs) {
//    delete node;  // todo 递归删除
//  }
//  for (auto& node: select_sql.having_conditions) {
//    delete node.left;  // todo 递归删除
//    delete node.right;
//  }
//  for (auto& node: select_sql.inner_join_conditions) {
//    delete node.left;  // todo 递归删除
//    delete node.right;
//  }
//  if (select_sql.condition.comp != CompOp::NO_OP) {
//    delete select_sql.condition.left;  // todo 递归删除
//    delete select_sql.condition.right;
//  }


  return RC::SUCCESS;
}
