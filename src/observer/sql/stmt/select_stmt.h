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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "group_by_stmt.h"

class FieldMeta;
class FilterStmt;
class OrderByStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt 
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override
  {
    return StmtType::SELECT;
  }

public:
  static RC create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const { return tables_; }

  std::vector<std::unique_ptr<Expression>> &project_expres() { return project_exprs_; }

  std::vector<std::string> &project_name() { return project_name_; }

  FilterStmt *filter_stmt() const { return filter_stmt_; }

  OrderByStmt *order_by_stmt() const { return order_by_stmt_; }

  GroupByStmt *group_by_stmt() const { return group_by_stmt_; }

  FilterStmt *having_stmt() const { return having_stmt_; }

  OrderByStmt *order_by_for_group_stmt() const { return order_by_for_group_stmt_; }

private:
  std::vector<Table *> tables_;
  FilterStmt *filter_stmt_ = nullptr; // where
  OrderByStmt *order_by_stmt_ = nullptr;  // order by
  GroupByStmt *group_by_stmt_ = nullptr;  // group by
  FilterStmt *having_stmt_ = nullptr; // having
  OrderByStmt *order_by_for_group_stmt_ = nullptr;

  std::vector<std::unique_ptr<Expression>> project_exprs_;  // 投影列的表达式
  std::vector<std::string> project_name_; // 投影列的名字
};
