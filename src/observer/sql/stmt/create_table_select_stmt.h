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

#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"

class Db;
class SelectStmt;
/**
 * @brief  通过select表示创建表的语句
 * @ingroup Statement
 * @details
 */
class CreateTableSelectStmt : public Stmt
{
public:
  CreateTableSelectStmt(const std::string &table_name, const std::vector<AttrInfoSqlNode> &attr_infos,
      SelectStmt * selects, Db *db)
        : table_name_(table_name),
          attr_infos_(attr_infos),
          select_stmt_(selects),
          db_(db)
  {}
  virtual ~CreateTableSelectStmt();

  StmtType type() const override { return StmtType::CREATE_TABLE_SELECT; }

  const std::string &table_name() const { return table_name_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }
  SelectStmt *select_stmt() const
  {
    return select_stmt_;
  }
  Db * get_db() const
  {
    return db_;
  }
  static RC create(Db *db, const CreateTableSelectSqlNode &create_table, Stmt *&stmt);

private:
  std::string table_name_;
  Db * db_ = nullptr;
  SelectStmt *select_stmt_ = nullptr;
  std::vector<AttrInfoSqlNode> attr_infos_;
};