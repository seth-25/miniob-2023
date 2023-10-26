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
// Created by Wangyunlai on 2022/07/08.
//

#include "sql/operator/index_scan_physical_operator.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"

IndexScanPhysicalOperator::IndexScanPhysicalOperator(
    Table *table, Index *index, bool readonly, 
    const Value *left_value, bool left_inclusive, 
    const Value *right_value, bool right_inclusive)
    : table_(table), 
      index_(index), 
      readonly_(readonly), 
      left_inclusive_(left_inclusive), 
      right_inclusive_(right_inclusive)
{
  if (left_value) {
    left_value_ = *left_value;
  }
  if (right_value) {
    right_value_ = *right_value;
  }
}

RC IndexScanPhysicalOperator::open(Trx *trx)
{
  if (nullptr == table_ || nullptr == index_) {
    return RC::INTERNAL;
  }

  const char *left;
  const char *right;
  int left_len = 0;
  int right_len = 0;
  int value_len = 0;
  int map_len = table_->table_meta().null_bitmap_field()->len();
  for (int i = 0; i < index_->index_meta().field_count(); i++) {
    const char *field_name = index_->index_meta().field()->at(i).c_str();
    value_len += table_->table_meta().field(field_name)->len();
  }

  char *left_with_bitmap = new char[map_len + value_len];
  char *right_with_bitmap = new char[map_len + value_len];
  if (nullptr != left_value_.data()) {
    memset(left_with_bitmap, 0, map_len + value_len);
    common::Bitmap left_map(left_with_bitmap, map_len);
    if (left_value_.attr_type() == AttrType::NULLS) {
      const char *field_name = index_->index_meta().field()->at(0).c_str();
      int field_id = table_->table_meta().field(field_name)->id();
      left_map.set_bit(field_id);
    }
    memcpy(left_with_bitmap + map_len, left_value_.data(), value_len);
    left = left_with_bitmap;
    left_len = map_len + value_len;
  } else {
    left = nullptr;
    left_len = left_value_.length();
  }

  if (nullptr != right_value_.data()) {
    memset(left_with_bitmap, 0, map_len + value_len);
    common::Bitmap right_map(right_with_bitmap, map_len);
    if (right_value_.attr_type() == AttrType::NULLS) {
      const char *field_name = index_->index_meta().field()->at(0).c_str();
      int field_id = table_->table_meta().field(field_name)->id();
      right_map.set_bit(field_id);
    }
    memcpy(right_with_bitmap + map_len, right_value_.data(), value_len);
    right = right_with_bitmap;
    right_len = map_len + value_len;
  } else {
    right = nullptr;
    right_len = right_value_.length();
  }
  IndexScanner *index_scanner =
      index_->create_scanner(left, left_len, left_inclusive_, right, right_len, right_inclusive_);
  delete[] left_with_bitmap;
  delete[] right_with_bitmap;
  record_handler_ = table_->record_handler();
  if (nullptr == record_handler_) {
    LOG_WARN("invalid record handler");
    index_scanner->destroy();
    return RC::INTERNAL;
  }
  index_scanner_ = index_scanner;

  tuple_.set_schema(table_, table_->table_meta().field_metas());

  trx_ = trx;
  return RC::SUCCESS;
}

RC IndexScanPhysicalOperator::next()
{
  RID rid;
  RC rc = RC::SUCCESS;

  record_page_handler_.cleanup();

  bool filter_result = false;
  while (RC::SUCCESS == (rc = index_scanner_->next_entry(&rid))) {
    rc = record_handler_->get_record(record_page_handler_, &rid, readonly_, &current_record_);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    tuple_.set_record(&current_record_);
    rc = filter(tuple_, filter_result);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (!filter_result) {
      continue;
    }

    rc = trx_->visit_record(table_, current_record_, readonly_);
    if (rc == RC::RECORD_INVISIBLE) {
      continue;
    } else {
      return rc;
    }
  }

  return rc;
}

RC IndexScanPhysicalOperator::close()
{
  index_scanner_->destroy();
  index_scanner_ = nullptr;
  return RC::SUCCESS;
}

Tuple *IndexScanPhysicalOperator::current_tuple()
{
//  tuple_.set_record(&current_record_);
  return &tuple_;
}

void IndexScanPhysicalOperator::set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC IndexScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC rc = RC::SUCCESS;
  Value value;
  for (std::unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}

std::string IndexScanPhysicalOperator::param() const
{
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}
