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
// Created by Wangyunlai on 2023/6/13.
//

#include "sql/stmt/create_table_select_stmt.h"
#include "event/sql_debug.h"
#include "sql/stmt/select_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "sql/expr/expression.h"
CreateTableSelectStmt::~CreateTableSelectStmt()
{
  if (nullptr != select_stmt_) {
    delete select_stmt_;
    select_stmt_ = nullptr;
  }
}
RC CreateTableSelectStmt::create(Db *db, const CreateTableSelectSqlNode &create_table, Stmt *&stmt)
{
  RC rc = RC::SUCCESS;

  Stmt *tmp_stmt = nullptr;
  rc = SelectStmt::create(db,create_table.selection,tmp_stmt);

  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct order by stmt");
    return rc;
  }
  SelectStmt *select_stmt = static_cast<SelectStmt *>(tmp_stmt);
  std::vector<AttrInfoSqlNode> attr_infos;

  if (!create_table.attr_infos.empty())
  {
     attr_infos = create_table.attr_infos;
  }else
  {
     for (size_t i = 0; i < select_stmt->project_name().size(); i ++ )
     {
       AttrInfoSqlNode attr_info;
       Expression * expr = select_stmt->project_expres()[i].get();
       attr_info.type = expr->value_type();
       attr_info.length = 4;
       attr_info.name = select_stmt->project_name()[i];
       bool nullable = true;
       FieldExpr::get_field_isnull_from_exprs(expr, nullable);
       attr_info.nullable = nullable;
       attr_infos.emplace_back(attr_info);
     }
  }

  auto * create_stmt =
      new CreateTableSelectStmt(create_table.relation_name, attr_infos,
          select_stmt, db);
  stmt = create_stmt;
//  sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}
