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
// Created by Wangyunlai on 2022/12/07.
//

#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/expr/expression.h"
#include "sql/stmt/order_by_stmt.h"

/**
 * @brief orderby逻辑算子
 * @ingroup LogicalOperator
 */
class OrderByLogicalOperator : public LogicalOperator
{
public:
  OrderByLogicalOperator(OrderByStmt *orderby_stmt) : orderby_stmt_(orderby_stmt)
  {}
  virtual ~OrderByLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::ORDER_BY;
  }
  OrderByStmt * orderByStmt()
  {
    return orderby_stmt_;
  }
private:
  OrderByStmt * orderby_stmt_ = nullptr;
};
