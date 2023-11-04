/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include "sql/stmt/insert_stmt.h"

#include <utility>
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "deps/common/lang/typecast.h"
#include "select_stmt.h"
#include "sql/expr/expression.h"
InsertStmt::InsertStmt(Table *table, std::vector<const Value *> values, int value_amount)
    : table_(table), values_(std::move(values)), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db, Trx* trx, InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, values_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  Stmt *tmp_stmt = nullptr;
  if (nullptr == table) {
    if (ViewMapHelper::get_instance()->get().count(table_name) != 0)
    {
      std::unordered_map<std::string, TableUnit *> parent_table_map;
      SelectStmt::create(db, trx, ViewMapHelper::get_instance()->get()[table_name], parent_table_map, tmp_stmt);
    } else {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
  }
  std::vector<std::vector<Value>> insert_values;
  if (tmp_stmt != nullptr)
  {
    SelectStmt *view_stmt = static_cast<SelectStmt *>(tmp_stmt);
    table_name = static_cast<FieldExpr *>(view_stmt->project_expres()[0].get())->table_name();
    table = db->find_table(table_name);
//    table = view_stmt->tables()[0]->table();  // insert只支持一张表
    if (table == nullptr)
    {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    const TableMeta &table_meta = table->table_meta();
    const int sys_field_num = table_meta.sys_field_num();
    const int field_num = table_meta.field_num() - table_meta.extra_filed_num();
    for (int u = 0; u < inserts.values.size(); u ++ ) {
      insert_values.emplace_back();
      for (int i = sys_field_num; i < field_num; i++) {
        const FieldMeta *field_meta = table_meta.field(i);
        const char *field_name = field_meta->name();
        bool found  = false;
        for (int j = 0; j < view_stmt->project_expres().size(); j++) {
          if (view_stmt->project_expres()[j]->type() != ExprType::FIELD) {
            LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
            return RC::SCHEMA_TABLE_NOT_EXIST;
          }
          const char* view_field_name = static_cast<FieldExpr *>(view_stmt->project_expres()[j].get())->field_name();
          if (strcmp(field_name, view_field_name) != 0) continue;
          found = true;
          insert_values[u].emplace_back(inserts.values[u][j]);
          break;
        }
        if (!found) {
          insert_values[u].emplace_back(Value());
        }
      }
    }
    delete view_stmt;
    view_stmt = nullptr;
    tmp_stmt = nullptr;
    inserts.values.swap(insert_values);
  }
  // check the fields number
  std::vector<const Value*> values;
  const int  value_num  = static_cast<int>(inserts.values[0].size());
  for (auto &x : inserts.values)
  {
    const Value * value = x.data();
    const int  temp_value_num  = static_cast<int>(x.size());
    const TableMeta &table_meta = table->table_meta();
    const int   field_num  = table_meta.field_num() - table_meta.sys_field_num() - table_meta.extra_filed_num();
    if (field_num != temp_value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", temp_value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // check fields type
    const int sys_field_num = table_meta.sys_field_num();
    for (int i = 0; i < value_num; i++) {
      const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
      const AttrType   field_type = field_meta->type();
      const AttrType   value_type = value[i].attr_type();
      if (AttrType::NULLS == value_type) {
        if (!field_meta->nullable()) {
          LOG_WARN("field type mismatch. can not be null. table=%s, field=%s, field type=%d, value_type=%d",
              table_name,
              field_meta->name(),
              field_type,
              value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
        continue;
      }
      if (field_type != value_type && !common::type_cast_check(value_type, field_type) && !TextHelper::isInsertText(field_type, value_type)) {
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
    values.emplace_back(value);
  }
  // everything alright
  stmt = new InsertStmt(table, values, value_num);
  return RC::SUCCESS;
}
