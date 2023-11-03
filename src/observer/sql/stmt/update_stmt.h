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

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/filter_stmt.h"

class Table;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt 
{
public:
  UpdateStmt() = default;
  UpdateStmt(TableUnit *table_unit,  std::vector<std::unique_ptr<Expression>>& exprs,
            std::vector<const FieldMeta *> &fields, FilterStmt *filter_stmt);
  ~UpdateStmt() override;

  StmtType type() const override
  {
    return StmtType::UPDATE;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }
  std::vector<std::unique_ptr<Expression>>& exprs()
  {
    return exprs_;
  }
  std::vector<const FieldMeta *>& fields()
  {
    return fields_;
  }
public:
  static RC create(Db *db, Trx* trx, const UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  TableUnit *table_unit() const
  {
    return table_unit_;
  }

private:
  TableUnit *table_unit_ = nullptr;
  std::vector<std::unique_ptr<Expression>> exprs_; // 需要更新的值
  std::vector<const FieldMeta *> fields_; // 需要更新的fields，和values一一对应
  FilterStmt *filter_stmt_ = nullptr;
};
