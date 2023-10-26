/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/orderby_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"

#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/expr/value_expression.h"
#include "sql/expr/comparison_expression.h"
#include "sql/expr/conjunction_expression.h"
#include "sql/operator/table_empty_logical_operator.h"
#include "sql/operator/groupby_logical_operator.h"

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;

  // 1. table_scan_oper
  unique_ptr<LogicalOperator> table_oper(nullptr);
  const std::vector<Table *> &tables = select_stmt->tables();
  std::vector<std::unique_ptr<Expression>> &project_expres = select_stmt->project_expres();
  for (Table *table : tables) {
    std::vector<Field> fields;
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, true/*readonly*/));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  // 2. predicate_oper
  unique_ptr<LogicalOperator> predicate_oper(nullptr);
  if (select_stmt->filter_stmt() != nullptr) {
    create_plan(select_stmt->filter_stmt(), predicate_oper);
  }

  // 3. order by for group
  unique_ptr<LogicalOperator> order_by_for_group_oper(nullptr);
  if (select_stmt->order_by_for_group_stmt() != nullptr) {
    order_by_for_group_oper = std::make_unique<OrderByLogicalOperator>(select_stmt->order_by_for_group_stmt());
  }

  // 4. group by
  unique_ptr<LogicalOperator> group_by_oper(nullptr);
  if (select_stmt->group_by_stmt() != nullptr) {
    group_by_oper = std::make_unique<GroupByLogicalOperator>(select_stmt->group_by_stmt());
  }

  // 5. having
  unique_ptr<LogicalOperator> having_oper(nullptr);
  if (select_stmt->having_stmt() != nullptr) {
    create_plan(select_stmt->having_stmt(), having_oper);
  }


  // 6. order by
  unique_ptr<LogicalOperator> orderby_oper(nullptr);
  if (select_stmt->order_by_stmt() != nullptr){
    orderby_oper = std::make_unique<OrderByLogicalOperator>(select_stmt->order_by_stmt());
  }

  // 7. project
  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(std::move(project_expres)));



  // 构造计划树
  // project -> sort(orderby) -> having(predicate) -> group by -> sort(group) -> pred -> scan
  unique_ptr<LogicalOperator> top_oper(nullptr); // 当前最上层的oper
  if (table_oper) {
    top_oper = std::move(table_oper);
  }
  if (predicate_oper) {
    predicate_oper->add_child(std::move(top_oper));
    top_oper = std::move(predicate_oper);
  }
  if (order_by_for_group_oper) {
    order_by_for_group_oper->add_child(std::move(top_oper));
    top_oper = std::move(order_by_for_group_oper);
  }
  if (group_by_oper) {
    group_by_oper->add_child(std::move(top_oper));
    top_oper = std::move(group_by_oper);
  }
  if (having_oper) {
    having_oper->add_child(std::move(top_oper));
    top_oper = std::move(having_oper);
  }
  if (orderby_oper) {
    orderby_oper->add_child(std::move(top_oper));
    top_oper = std::move(orderby_oper);
  }

  if (top_oper) {
    project_oper->add_child(std::move(top_oper));
  }
  else {  // select func，没有from 和 where，没有table_oper和predicate_oper
    unique_ptr<LogicalOperator> empty_oper(new TableEmptyLogicalOperator());
    project_oper->add_child(std::move(empty_oper));
  }

  logical_operator.swap(project_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  for (FilterUnit *filter_unit : filter_units) {
    std::unique_ptr<Expression>& left = filter_unit->left();
    std::unique_ptr<Expression>& right = filter_unit->right();
    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = insert_stmt->table();

  vector<vector<Value>> values;
  for (size_t i = 0; i < insert_stmt->values().size();i ++ )
  {
    vector<Value> value(insert_stmt->values()[i], insert_stmt->values()[i] + insert_stmt->value_amount());
    values.emplace_back(value);
  }

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = delete_stmt->table();
  FilterStmt *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = update_stmt->table();

  FilterStmt *filter_stmt = update_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  create_plan(filter_stmt, predicate_oper);

  UpdateLogicalOperator *update_operator = new UpdateLogicalOperator(
      update_stmt->table(), std::move(update_stmt->values()), std::move(update_stmt->fields()));
  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_operator->add_child(std::move(predicate_oper));
  } else {
    update_operator->add_child(std::move(table_get_oper));
  }

  logical_operator.reset(update_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
