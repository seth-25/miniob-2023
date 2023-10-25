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
#include "sql/stmt/group_by_stmt.h"

/**
 * @brief orderby逻辑算子
 * @ingroup LogicalOperator
 */
class GroupByLogicalOperator : public LogicalOperator
{
public:
  GroupByLogicalOperator(GroupByStmt *group_by_stmt) {
    group_by_field_exprs_ = std::move(group_by_stmt->group_by_field_exprs());
    aggr_exprs_ = std::move(group_by_stmt->aggr_exprs());
    field_exprs_ = std::move(group_by_stmt->field_exprs());
  }
  virtual ~GroupByLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::GROUP_BY; }

  std::vector<std::unique_ptr<FieldExpr>>& group_by_field_exprs() { return group_by_field_exprs_; }
  std::vector<std::unique_ptr<Expression>>& aggr_exprs() { return aggr_exprs_; }
  std::vector<std::unique_ptr<Expression>>& field_exprs() { return field_exprs_; }

private:
  std::vector<std::unique_ptr<FieldExpr>> group_by_field_exprs_; // 需要分组的字段
  // sql执行顺序：record -> where -> group by -> order by -> having -> 投影
  // 所以group by后面需要记录having和投影的字段计算结果，不需要记录where的字段
  // 投影列和having的所有字段：
  std::vector<std::unique_ptr<Expression>> aggr_exprs_; // 聚集表达式的字段
  std::vector<std::unique_ptr<Expression>> field_exprs_;   // 非聚集表达式的字段
};
