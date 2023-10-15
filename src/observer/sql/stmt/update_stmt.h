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
//  UpdateStmt(Table *table, Value *values, int value_amount);
  UpdateStmt(Table *table, const Value *value,
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
  const Value* value() const
  {
    return value_;
  }
  std::vector<const FieldMeta *>& fields()
  {
    return fields_;
  }
public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table *table() const
  {
    return table_;
  }

private:
  Table *table_ = nullptr;
  const Value * value_; // 需要更新的值
  std::vector<const FieldMeta *> fields_; // 需要更新的fields，和values一一对应
  FilterStmt *filter_stmt_ = nullptr;
};
