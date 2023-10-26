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
// Created by WangYunlai on 2022/12/27.
//

#include <sstream>
#include "sql/operator/createselect_physical_operator.h"
#include "common/log/log.h"
#include "storage/trx/trx.h"

using namespace std;

RC CreateselectPhysicalOperator::open(Trx * trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  int attr_count = static_cast<int>(attrinfos_.size());
  rc = db_->create_table(table_name_.c_str(), attr_count, attrinfos_.data());
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open create table %s : %s", table_name_.c_str(), strrc(rc));
    return rc;
  }
  table_ = db_->find_table(table_name_.c_str());
  if (table_ == nullptr)
  {
    rc = RC::SCHEMA_TABLE_NOT_EXIST;
    LOG_WARN("failed to find table %s : %s", table_name_.c_str(), strrc(rc));
    return rc;
  }
  trx_ = trx;

  return RC::SUCCESS;
}

RC CreateselectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

RC CreateselectPhysicalOperator::next()
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  RC rc = RC::SUCCESS;
  while (RC::SUCCESS == (rc = children_[0]->next()))
  {
    Record record;
    Tuple * tuple_current = children_[0]->current_tuple();
    int value_count = tuple_current->cell_num();
    std::vector<Value> values;
    for (int i = 0; i < value_count; i ++ )
    {
        Value value;
        rc = tuple_current->cell_at(i, value);
        if (rc != RC::SUCCESS)
        {
          LOG_WARN("failed to find cellat %s : %s",  strrc(rc));
          return rc;
        }
        values.emplace_back(value);
    }
    rc = table_->make_record(value_count, values.data(), record);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to make record. rc=%s", strrc(rc));
        return rc;
    }
    rc = trx_->insert_record(table_, record);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
        return rc;
    }
    values.clear();
  }

  return rc;
}

Tuple *CreateselectPhysicalOperator::current_tuple()
{
  return nullptr;
}
