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
// Created by WangYunlai on 2022/6/27.
//

#pragma once

#include <memory>
#include "sql/operator/physical_operator.h"
#include "sql/expr/expression.h"

class OrderByStmt;

/**
 * @brief orderby物理算子
 * @ingroup PhysicalOperator
 */
class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator(OrderByStmt *orderby_stmt) : orderby_stmt_(orderby_stmt)
  {}

  virtual ~OrderByPhysicalOperator()
  {
    for (auto &cpd_rcd : st_) {
      for (auto rcd : cpd_rcd) {
        delete rcd;
      }
    }
  }
  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::ORDER_BY;
  }
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  RC fetch_and_sort_table();

private:
  OrderByStmt *orderby_stmt_ = nullptr;
  bool is_first_ = true;

  std::vector<CompoundRecord> st_;  // sort table
  std::vector<int> ordered_idx_;
  std::vector<int>::iterator it_;
};
