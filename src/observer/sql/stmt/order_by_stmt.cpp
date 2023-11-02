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

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/stmt/filter_stmt.h"

OrderByStmt::~OrderByStmt()
{
  for (OrderByUnit *unit : orderby_units_) {
    delete unit;
  }
  orderby_units_.clear();
}

RC OrderByStmt::create(Db *db, TableUnit* default_table, std::unordered_map<std::string, TableUnit*> *tables,
    const OrderBySqlNode *orderbys, int orderby_num, OrderByStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  OrderByStmt *tmp_stmt = new OrderByStmt();
  for (int i = 0; i < orderby_num; i++) {
    OrderByUnit *orderby_unit = nullptr;
    rc = create_orderby_unit(db, default_table, tables, orderbys[i], orderby_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->orderby_units_.push_back(orderby_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

// 获取对应的表和字段


RC OrderByStmt::create_orderby_unit(Db *db, TableUnit* default_table, std::unordered_map<std::string, TableUnit*> *tables,
    const OrderBySqlNode &orderby, OrderByUnit *&orderby_unit)
{

  RC rc = RC::SUCCESS;

  bool sort_type = orderby.is_asc;

//  Expression *expr = nullptr;
//  Table *table = nullptr;
//  const FieldMeta *field = nullptr;
//  rc = get_table_and_field(db, default_table, tables, orderby.attribute, table, field);
//  expr = new FieldExpr(table, field);

  FieldExpr* field_expr;
  rc = gen_field_expr(default_table, tables, orderby.attribute, field_expr);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot find attr");
    return rc;
  }
  orderby_unit = new OrderByUnit;
  orderby_unit->set_sort_type(sort_type);
  orderby_unit->set_expr((Expression*) field_expr);
  return rc;
}
