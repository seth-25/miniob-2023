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
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include <iostream>
#include "storage/table/table.h"
#include "storage/field/field_meta.h"
#include "sql/expr/expression.h"

class TupleCellSpec
{
public:
//  TupleCellSpec(const char *table_name, const char *field_name, const char *alias = nullptr);
  TupleCellSpec(const char *alias) {
    if (alias) {
      alias_ = alias;
    }
  };
  TupleCellSpec(std::shared_ptr<Expression> &&expression): expression_(std::move(expression)) {};

  const char *alias() const
  {
    return alias_.c_str();
  }
  const Expression* expression() const {
    return expression_.get();
  }

private:
  std::string alias_;
  std::shared_ptr<Expression> expression_;
};
