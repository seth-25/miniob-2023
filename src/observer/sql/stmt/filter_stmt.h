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

#pragma once

#include <vector>
#include <unordered_map>
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

class FilterUnit 
{
public:
  FilterUnit() = default;
  ~FilterUnit()
  {
    if (left_unit_) {
      delete left_unit_;
      left_unit_ = nullptr;
    }
    if (right_unit_) {
      delete right_unit_;
      right_unit_ = nullptr;
    }
  }

  void set_comp(CompOp comp) {
    comp_ = comp;
  }

  CompOp comp() const {
    return comp_;
  }

  void set_left(std::unique_ptr<Expression>& expr) {
    left_ = std::move(expr);
  }
  void set_right(std::unique_ptr<Expression>& expr) {
    right_ = std::move(expr);
  }
  std::unique_ptr<Expression>& left() {
    return left_;
  }
  std::unique_ptr<Expression>& right() {
    return right_;
  }

  void set_left_unit(FilterUnit *unit)
  {
    assert(CompOp::AND_OP == comp_ || CompOp::OR_OP == comp_);
    left_unit_ = unit;
  }
  void set_right_unit(FilterUnit *unit)
  {
    assert(CompOp::AND_OP == comp_ || CompOp::OR_OP == comp_);
    right_unit_ = unit;
  }
  FilterUnit *left_unit() const
  {
    assert(CompOp::AND_OP == comp_ || CompOp::OR_OP == comp_);
    return left_unit_;
  }
  FilterUnit *right_unit() const
  {
    assert(CompOp::AND_OP == comp_ || CompOp::OR_OP == comp_);
    return right_unit_;
  }

private:
  CompOp comp_ = NO_OP;
  std::unique_ptr<Expression>  left_;
  std::unique_ptr<Expression>  right_;

 /**
 * 用AND或OR连接时，词法会递归创建unit树
 * 比如a AND b OR c OR d AND e
 * 需要使用下面的结构表示：
 *              or
 *           /     \
 *        or        and
 *       /  \      /  \
 *     and   c    d    e
 *    /  \
 *   a    b
 *
 */
  FilterUnit *left_unit_ = nullptr;
  FilterUnit *right_unit_ = nullptr;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt 
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const
  {
    return filter_units_;
  }

public:
  static RC create(Db *db, Trx* trx, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Trx* trx, Table *default_table, std::unordered_map<std::string, Table *> *table_map,
      const ConditionSqlNode &condition, FilterUnit *&filter_unit);

private:
  std::vector<FilterUnit *> filter_units_;
};
RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field);