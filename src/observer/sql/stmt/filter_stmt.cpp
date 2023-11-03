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
// Created by Wangyunlai on 2022/5/22.
//

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Trx* trx, TableUnit* default_table, std::unordered_map<std::string, TableUnit*> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) { // and隔开的每个条件
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, trx, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}


RC FilterStmt::create_filter_unit(Db *db, Trx* trx, TableUnit* default_table, std::unordered_map<std::string, TableUnit*> *table_map,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp; // 比较条件，如>, <=
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  if (comp == AND_OP || comp == OR_OP) {
    assert(condition.left->type == ExprSqlNodeType::CONDITION);
    assert(condition.right->type == ExprSqlNodeType::CONDITION);
    FilterUnit *left_unit = nullptr;
    FilterUnit *right_unit = nullptr;
    rc = create_filter_unit(db, trx, default_table, table_map, *condition.left->condition_expr, left_unit);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("filter unit create left expression failed");
      return rc;
    }
    rc = create_filter_unit(db, trx, default_table, table_map, *condition.right->condition_expr, right_unit);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("filter unit create left expression failed");
      delete left_unit;
      return rc;
    }
    filter_unit = new FilterUnit;
    filter_unit->set_comp(comp);
    filter_unit->set_left_unit(left_unit);
    filter_unit->set_right_unit(right_unit);
    return rc;
  }

  filter_unit = new FilterUnit;

  std::unique_ptr<Expression> left;
  std::unique_ptr<Expression> right;
  assert(condition.left != nullptr && condition.right != nullptr);
  rc = Expression::create_expression(condition.left, left, *table_map, default_table, comp, db, trx);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("filter unit create left expression failed");
    return rc;
  }

  rc = Expression::create_expression(condition.right, right, *table_map, default_table, comp, db, trx);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("filter unit create right expression failed");
    return rc;
  }



  filter_unit = new FilterUnit;
  filter_unit->set_comp(comp);
  filter_unit->set_left(left);
  filter_unit->set_right(right);

  // 检查两个类型是否能够比较
  return rc;
}


// 获取对应的表和字段
RC get_table_and_field(Db *db, Table* default_table, std::unordered_map<std::string, Table*> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;  // select * from t where id=1，未指定id的表名，设定id为t表
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC gen_field_expr(TableUnit* default_table, std::unordered_map<std::string, TableUnit*> *table_map, const RelAttrSqlNode &attr, FieldExpr*& field_expr) {
  TableUnit* table_unit;
  if (common::is_blank(attr.relation_name.c_str())) {
    table_unit = default_table;  // select * from t where id=1，未指定id的表名，设定id为t表
  }
  else {
    auto iter = table_map->find(attr.relation_name);
    if (iter != table_map->end()) {
      table_unit = iter->second;
    }
    else {
      LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
  }

  if (table_unit->is_table())
  {
    const Table *table = table_unit->table();
    const FieldMeta *field_meta = table->table_meta().field(attr.attribute_name.c_str());
    if (nullptr == field_meta)
    {
      LOG_WARN("no such field. field=%s.%s",  table->name(), attr.attribute_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_expr = new FieldExpr(table, field_meta);
  }
  else
  {
    SelectStmt* view_stmt = table_unit->view_stmt();
    shared_ptr<Expression> view_expr;
    RC rc = Expression::find_expr(view_stmt->project_expres(), view_expr, attr.attribute_name.c_str(), false);
    if (rc != RC::SUCCESS) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_expr = new FieldExpr(view_expr, table_unit->view_name());
  }
  assert(field_expr != nullptr);
  return RC::SUCCESS;
}