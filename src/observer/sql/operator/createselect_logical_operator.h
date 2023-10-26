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
// Created by WangYunlai on 2022/12/27.
//

#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/db/db.h"
/**
 * @brief create_table_select逻辑算子
 * @ingroup LogicalOperator
 */
class CreateselectLogicalOperator : public LogicalOperator
{
public:
  CreateselectLogicalOperator(Db* db, const std::string &&table_name, const std::vector<AttrInfoSqlNode> && attrinfos):
  db_(db), table_name_(table_name), attrinfos_(attrinfos)
  {}
  virtual ~CreateselectLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::CREATE_SELECT;
  }
  Db  *get_db() const
  {
    return db_;
  }
  const std::vector<AttrInfoSqlNode> &get_attrinfos() const
  {
    return attrinfos_;
  }

  const std::string &get_name() const
  {
    return table_name_;
  }

private:
  Db *db_ = nullptr;
  std::vector<AttrInfoSqlNode> attrinfos_;
  std::string table_name_;

};
