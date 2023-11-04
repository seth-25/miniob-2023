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

#include "storage/table/table.h"
#include "storage/db/db.h"
#include "sql/stmt/update_stmt.h"

#include <utility>
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/typecast.h"
#include "sql/expr/value_expression.h"
#include "sql/expr/subquery_expression.h"

// UpdateStmt::UpdateStmt(Table *table, Value *values, int value_amount)
//    : table_(table), values_(values), value_amount_(value_amount)
//{}
UpdateStmt::UpdateStmt(TableUnit *table_unit, std::vector<std::unique_ptr<Expression>>& exprs,
    std::vector<const FieldMeta *> &fields, FilterStmt *filter_stmt)
    : table_unit_(table_unit), exprs_(std::move(exprs)), fields_(fields), filter_stmt_(filter_stmt)
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, Trx* trx, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  TableUnit* table_unit = nullptr;
  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    SelectStmt* view_stmt = nullptr;
    if (RC::SUCCESS == SelectStmt::init_view(table_name, db, trx, view_stmt)) {  // 判断是否是view, 如果是则初始化view的条件
      table_unit = new TableUnit(view_stmt, table_name);
      if (table_unit->view_stmt()->tables().empty() || !table_unit->view_stmt()->tables()[0]->is_table()) {
        LOG_WARN("找不到视图的创建语句的table，暂不支持视图套视图的update");
        return RC::NOTFOUND;
      }
      else {
        table = table_unit->view_stmt()->tables()[0]->table();  // update只支持一张表
      }
    }
    else {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
  }
  else {
    table_unit = new TableUnit(table, "");  // update 暂不支持别名
  }


  vector<const FieldMeta *> fields;
  vector<unique_ptr<Expression>> exprs;

  for (size_t i = 0; i < update.update_values.size(); i ++ )
  {
    bool field_exist = false;
    const char *attr_name = update.update_values[i].attribute_name.c_str();
    const ExprSqlNode* expr_node = update.update_values[i].expr;
    if (nullptr == attr_name) {
      LOG_WARN("invalid argument. attribute_name=%p", attr_name);
      return RC::INVALID_ARGUMENT;
    }

    // if (table_unit->is_table()) // todo 考虑view的时候用别名
    const TableMeta &table_meta = table->table_meta();
    const int sys_field_num = table_meta.sys_field_num();
    const int field_num = table_meta.field_num() - table_meta.extra_filed_num();

    // 找到属性对应字段，sys_field_num到field_num之间是用户创建的field
    for (int j = sys_field_num; j < field_num; j ++ ) {
      const FieldMeta *field_meta = table_meta.field(j);
      const char *field_name = field_meta->name();  // todo 考虑view这列是别名
      if (strcmp(field_name, attr_name) != 0) continue; // 检查update set的字段是否存在
      field_exist = true;

      unique_ptr<Expression> expr;
      const std::unordered_map<std::string, TableUnit *> table_map;
      if (ExprSqlNodeType::UNARY == expr_node->type) {
        const UnaryExprSqlNode *unary_expr_node = expr_node->unary_expr;
        if (unary_expr_node->is_attr) {
          return RC::SQL_SYNTAX;
        }
        RC rc = ValueExpr::create_expression(expr_node, expr);
        if (RC::SUCCESS != rc) {
          LOG_ERROR("UpdateStmt Create ValueExpr Failed. RC = %d:%s", rc, strrc(rc));
          return rc;
        }
      } else if (ExprSqlNodeType::SUBQUERY == expr_node->type) {
        // will check projects num
        RC rc = SubQueryExpr::create_expression(expr_node, expr, table_map, CompOp::EQUAL_TO, db, trx);
        if (RC::SUCCESS != rc) {
          LOG_ERROR("UpdateStmt Create SubQueryExpression Failed. RC = %d:%s", rc, strrc(rc));
          return rc;
        }
      } else {
        return RC::SQL_SYNTAX;
      }

      assert(expr != nullptr);
      exprs.emplace_back(std::move(expr));

      fields.emplace_back(field_meta);
    }


    if (!field_exist) {
      LOG_WARN("Field %s.%s is not exist", table_name, attr_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }

  assert(fields.size() == exprs.size());

  std::unordered_map<std::string, TableUnit *> table_map;
  table_map.insert(std::pair<std::string, TableUnit *>(std::string(table_name), table_unit));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, trx, table_unit, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }


  // everything alright
  stmt = new UpdateStmt(table_unit, exprs, fields, filter_stmt);
  return RC::SUCCESS;
}
