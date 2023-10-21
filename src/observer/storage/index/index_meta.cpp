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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString UNIQUE_OR_NOT("unique");
const static Json::StaticString FIELD_FIELD_NAME("field_name");

RC IndexMeta::init(const char *name, bool is_unique, std::vector<const FieldMeta *> &fields)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  std::vector<std::string> fields_string;
  fields_string.reserve(fields.size());
  for (auto & field : fields)
  {
    fields_string.emplace_back((*field).name());
  }

  is_unique_ = is_unique;
  name_ = name;
  fields_.swap(fields_string);
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  json_value[UNIQUE_OR_NOT] = is_unique_;
  for (size_t i = 0; i < fields_.size(); i++) {
    int idx = i;
    json_value[FIELD_FIELD_NAME][idx] = fields_[idx];
  }
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &unique_value = json_value[UNIQUE_OR_NOT];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  if (!unique_value.isBool()) {
    LOG_ERROR("Unique is not a boolean. json value=%s", unique_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  std::vector<const FieldMeta *> fields;
  for (size_t i = 0; i < field_value.size(); i++) {
    int idx = i;
    if (!field_value[idx].isString()) {
      LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
          name_value.asCString(),
          field_value.toStyledString().c_str());
      return RC::INTERNAL;
    }

    const FieldMeta *field = table.field(field_value[idx].asCString());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value[idx].asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.emplace_back(field);
  }

  return index.init(name_value.asCString(), unique_value.asBool(), fields);
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const int IndexMeta::field_count() const
{
  return fields_.size();
}

const std::vector<std::string> *IndexMeta::field() const
{
  return &fields_;
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", field=" << fields_[0];

  for (size_t i = 1; i < fields_.size(); i++) {
    os << ',' << fields_[i];
  }
}