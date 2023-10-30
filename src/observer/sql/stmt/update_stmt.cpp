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

#include "storage/table/table.h"
#include "storage/db/db.h"
#include "sql/stmt/update_stmt.h"

#include <utility>
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/typecast.h"

// UpdateStmt::UpdateStmt(Table *table, Value *values, int value_amount)
//    : table_(table), values_(values), value_amount_(value_amount)
//{}
UpdateStmt::UpdateStmt(Table *table, std::vector<Value>& values,
    std::vector<const FieldMeta *> &fields, FilterStmt *filter_stmt)
    : table_(table), values_(std::move(values)), fields_(fields), filter_stmt_(filter_stmt)
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, Trx* trx, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::vector<const FieldMeta *> fields;
  std::vector<Value> values;
//  const Value *value = nullptr;

  // todo 支持多值update修改
  for (size_t i = 0; i < update.update_values.size(); i ++ )
  {
    bool field_exist = false;
    const char *attr_name = update.update_values[i].attribute_name.c_str();
    if (nullptr == attr_name) {
      LOG_WARN("invalid argument. attribute_name=%p", attr_name);
      return RC::INVALID_ARGUMENT;
    }


    const TableMeta &table_meta = table->table_meta();
    const int sys_field_num = table_meta.sys_field_num();
    const int field_num = table_meta.field_num() - table_meta.extra_filed_num();
    // 找到属性对应字段，sys_field_num到field_num之间是用户创建的field
    for (int j = sys_field_num; j < field_num; j ++ ) {
      const FieldMeta *field_meta = table_meta.field(j);
      const char *field_name = field_meta->name();
      if (strcmp(field_name, attr_name) != 0) continue;
      field_exist = true;
      Value value = update.update_values[i].value;
      values.emplace_back(value);

      // 检查类型
      const AttrType field_type = field_meta->type();
      const AttrType value_type = value.attr_type();
      if (AttrType::NULLS == value_type) {
        if (!field_meta->nullable()) {
          LOG_WARN("field type mismatch. can not be null. table=%s, field=%s, field type=%d, value_type=%d",
              table_name,
              field_meta->name(),
              field_type,
              value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
        fields.emplace_back(field_meta);
        continue;
      }
      if (field_type != value_type && !common::type_cast_check(value_type, field_type) && !TextHelper::isInsertText(field_type, value_type)) {
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
        table_name, field_meta->name(), field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }

      fields.emplace_back(field_meta);
    }

    if (!field_exist) {
      LOG_WARN("Field %s.%s is not exist", table_name, attr_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, trx, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }


  // everything alright
  stmt = new UpdateStmt(table, values, fields, filter_stmt);
  return RC::SUCCESS;
}
