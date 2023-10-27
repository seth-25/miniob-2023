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
// Created by WangYunlai on 2022/6/27.
//

#include "common/log/log.h"
#include "sql/operator/orderby_physical_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/field/field.h"
//todo 支持事务
RC OrderByPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC OrderByPhysicalOperator::fetch_and_sort_table()
{

  RC rc = RC::SUCCESS;
  int index = 0;
  typedef std::pair<std::vector<Value>, int> CmpPair;
  std::vector<CmpPair> pair_sort_table;
  std::vector<Value> pair_cell;

  auto &units = orderby_stmt_->orderby_units();
  while (RC::SUCCESS == (rc = children_[0]->next())) {
    // construct pair sort table
    // 1 cons vector<cell>
    pair_cell.clear();
    for (const OrderByUnit *unit : units) {
      Expression *expr = unit->expr();
      Value cell;
      expr->get_value(*children_[0]->current_tuple(), cell);
      pair_cell.emplace_back(cell);
    }
    // 2 cons pair
    // 3 cons pair vector
    pair_sort_table.emplace_back(std::make_pair(pair_cell, index++));
    // store child records
    CompoundRecord cpd_rcd;
    CompoundRecord cpd_rcd_after;
    children_[0]->current_tuple()->get_record(cpd_rcd);
    // need to deep copy the rcd and push back to rht
    // remember to delete them in dtor
    for (auto &rcd_ptr : cpd_rcd) {
      Record *rcd_ptr_after = new Record();
      rcd_ptr_after->copy_data(*rcd_ptr);
      cpd_rcd_after.emplace_back(rcd_ptr_after);
    }
    st_.emplace_back(cpd_rcd_after);
  }
  if (RC::RECORD_EOF != rc) {
    LOG_ERROR("Fetch Table Error In OrderByPhysicalOperator. RC: %d", rc);
    return rc;
  }
  rc = RC::SUCCESS;
  LOG_INFO("Fetch Table Success In OrderByPhysicalOperator");
  // print_info();

  // then sort table
  bool order[units.size()];  // specify 1 asc or 2 desc
  for (std::vector<OrderByUnit *>::size_type i = 0; i < units.size(); ++i) {
    order[i] = units[i]->sort_type();
  }
  // consider null
  auto cmp = [&order](const CmpPair &a, const CmpPair &b) {
    auto &cells_a = a.first;
    auto &cells_b = b.first;
    assert(cells_a.size() == cells_b.size());
    for (size_t i = 0; i < cells_a.size(); ++i) {
      auto &cell_a = cells_a[i];
      auto &cell_b = cells_b[i];
      if (cell_a.is_null() && cell_b.is_null()) {
        continue;
      }
      if (cell_a.is_null()) {
        return order[i];
      }
      if (cell_b.is_null()) {
        return !order[i];
      }
      if (cell_a != cell_b) {
        return order[i] ? cell_a < cell_b : cell_a > cell_b;
      }
    }
    return false;  // completely same
  };
  std::sort(pair_sort_table.begin(), pair_sort_table.end(), cmp);
  LOG_INFO("Sort Table Success In OrderByPhysicalOperator");

  // fill ordered_idx_
  for (size_t i = 0; i < pair_sort_table.size(); ++i) {
    ordered_idx_.emplace_back(pair_sort_table[i].second);
  }
  it_ = ordered_idx_.begin();

  return rc;  // return RC::SUCCESS
}


RC OrderByPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  // at first cache child tuple and sort them
  if (is_first_) {
    is_first_ = false;
    rc = fetch_and_sort_table();
    if (RC::SUCCESS != rc) {
      return rc;
    }
  }
  if (ordered_idx_.end() != it_) {
    // NOTE: PAY ATTENTION HERE

    children_[0]->current_tuple()->set_record(st_[*it_]);
    it_++;
    return RC::SUCCESS;
  }
  return RC::RECORD_EOF;
}

RC OrderByPhysicalOperator::close()
{
  RC rc = RC::SUCCESS;
  children_[0]->close();
  return rc;
}

Tuple *OrderByPhysicalOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

