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
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "common/rc.h"

class Table;

/**
 * @brief 表扫描物理算子
 * @ingroup PhysicalOperator
 */
class TableEmptyPhysicalOperator : public PhysicalOperator
{
public:
  TableEmptyPhysicalOperator() = default;
  virtual ~TableEmptyPhysicalOperator() = default;
  PhysicalOperatorType type() const override {
    return PhysicalOperatorType::TABLE_EMPTY;
  }
  RC open(Trx *trx) override {
    return RC::SUCCESS;
  }
  RC next() override {
    if (first_) {
      first_ = false;
      return RC::SUCCESS;
    }
    return RC::RECORD_EOF;
  }
  RC close() override{
    return RC::SUCCESS;
  }

  Tuple *current_tuple() override{
    return &tuple_;
  }

private:
  EmptyTuple tuple_;
  bool     first_ = true;
};
