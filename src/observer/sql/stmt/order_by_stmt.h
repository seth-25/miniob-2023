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


class OrderByUnit
{
public:
  OrderByUnit() = default;
  ~OrderByUnit()
  {
    if (expr_) {
      delete expr_;
      expr_ = nullptr;
    }
  }

  void set_sort_type(bool sort_type)
  {
    is_asc_ = sort_type;
  }

  bool sort_type() const
  {
    return is_asc_;
  }
  void set_expr(Expression *expr)
  {
    expr_ = expr;
  }
  Expression *expr() const
  {
    return expr_;
  }

private:
  bool is_asc_ = true;
  Expression *expr_ = nullptr;
};

/**
 * @brief order by语句
 * @ingroup Statement
 */
class OrderByStmt
{
public:
  OrderByStmt() = default;
  virtual ~OrderByStmt();

public:
  const std::vector<OrderByUnit *> &orderby_units() const
  {
    return orderby_units_;
  }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const OrderBySqlNode *orderbys, int orderby_num, OrderByStmt *&stmt);

  static RC create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const OrderBySqlNode &orderby, OrderByUnit *&orderby_unit);

private:
  std::vector<OrderByUnit *> orderby_units_;
};
