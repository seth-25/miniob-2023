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

#include "sql/operator/physical_operator.h"
#include "storage/db/db.h"

/**
 * @brief create_table_select物理算子
 * @ingroup PhysicalOperator
 */
class CreateselectPhysicalOperator : public PhysicalOperator
{
public:
  CreateselectPhysicalOperator(Db* db, const std::string &&table_name, const std::vector<AttrInfoSqlNode> && attrinfos):
   db_(db), table_name_(table_name), attrinfos_(attrinfos)
  {}
  virtual ~CreateselectPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::CREATE_SELECT;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;


private:
  Db *db_ = nullptr;
  std::vector<AttrInfoSqlNode> attrinfos_;
  std::string table_name_;
  Trx *trx_ = nullptr;
  Table *table_ = nullptr;


};
