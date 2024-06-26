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
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <memory>
#include <vector>
#include <string>

#include "common/log/log.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse.h"
#include "sql/parser/value.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"
#include "common/lang/bitmap.h"

class Table;

/**
 * @defgroup Tuple
 * @brief Tuple 元组，表示一行数据，当前返回客户端时使用
 * @details
 * tuple是一种可以嵌套的数据结构。
 * 比如select t1.a+t2.b from t1, t2;
 * 需要使用下面的结构表示：
 * @code {.cpp}
 *  Project(t1.a+t2.b)
 *        |
 *      Joined
 *      /     \
 *   Row(t1) Row(t2)
 * @endcode
 *
 */

/**
 * @brief 元组的结构，包含哪些字段(这里成为Cell)，每个字段的说明
 * @ingroup Tuple
 */
class TupleSchema
{
public:
  virtual ~TupleSchema()
  {
    for (auto cell : cells_) {
      delete cell;
    }
    cells_.clear();
  }

  void append_cell(TupleCellSpec *cell) { cells_.emplace_back(cell); }

  void append_cell(const char *alias) { append_cell(new TupleCellSpec(alias)); }

  int cell_num() const { return static_cast<int>(cells_.size()); }

  const TupleCellSpec *cell_at(int i) const { return cells_[i]; }


private:
  std::vector<TupleCellSpec *> cells_;
};

/**
 * @brief 元组的抽象描述
 * @ingroup Tuple
 */
class Tuple
{
public:
  Tuple()          = default;
  virtual ~Tuple() = default;

  /**
   * @brief 获取元组中的Cell的个数
   * @details 个数应该与tuple_schema一致
   */
  virtual int cell_num() const = 0;

  /**
   * @brief 获取指定位置的Cell
   *
   * @param index 位置
   * @param[out] cell  返回的Cell
   */
  virtual RC cell_at(int index, Value &cell) const = 0;

  /**
   * @brief 根据cell的描述，获取cell的值
   * 目前只支持spec里存的Expression是fieldExpr
   * @param spec cell的描述
   * @param[out] cell 返回的cell
   */
  virtual RC find_cell(const TupleCellSpec &spec, Value &cell) const = 0;

  virtual void get_record(CompoundRecord &record) const = 0;

  // this func will set all records
  // invoke this func will erase begin arg:record
  virtual void set_record(CompoundRecord &record) = 0;

  // this will not set all records
  // invoke this func will erase end arg:record
  virtual void set_right_record(CompoundRecord &record) = 0;

  virtual std::string to_string() const
  {
    std::string str;
    const int cell_num = this->cell_num() - 1;  // 最后一列是null
    for (int i = 0; i < cell_num - 1; i++) {
      Value cell;
      cell_at(i, cell);
      str += cell.to_string();
      str += ", ";
    }

    if (cell_num > 0) {
      Value cell;
      cell_at(cell_num - 1, cell);
      str += cell.to_string();
    }
    return str;
  }
};

class EmptyTuple : public Tuple
{
public:
  EmptyTuple()          = default;
  virtual ~EmptyTuple() = default;

  int  cell_num() const override { return 0; }

  void get_record(CompoundRecord &record) const override {}

  void set_record(CompoundRecord &record) override {}

  void set_right_record(CompoundRecord &record) override {}

  RC cell_at(int index, Value &cell) const override { return RC::SUCCESS; }

  RC find_cell(const TupleCellSpec &spec, Value &cell) const override { return RC::SUCCESS; }
};

/**
 * @brief 一行数据的元组
 * find_cell和cell_at只支持fieldExpr
 * @ingroup Tuple
 * @details 直接就是获取表中的一条记录
 */
class RowTuple : public Tuple
{
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    for (FieldExpr *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_record(Record *record)
  {
    this->record_                    = record;
    const FieldExpr *filed_expr      = this->speces_.back();
    const FieldMeta *null_filed_meta = filed_expr->field().meta();
    this->bitmap_.init(record->data() + null_filed_meta->offset(), null_filed_meta->len());
  }

  void set_schema(const Table *table, const string& table_alias, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    table_alias_ = table_alias;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new FieldExpr(table, table_alias, &field));
    }
  }

  void clear_schema() {
    speces_.clear();
  }

  int cell_num() const override {
    return speces_.size();
  }

  /**
   * 根据index，获取第i个字段的值
   */
  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    FieldExpr *field_expr = speces_[index];
    const FieldMeta *field_meta = field_expr->field().meta();
    if (bitmap_.get_bit(index)) {
      cell.set_null();
    } else {
      cell.set_type(field_meta->type());
      if (field_meta->type() == TEXTS) {
        TextRecord &text_record = *(TextRecord*)(this->record_->data() + field_meta->offset());
        char* str = this->record_->get_text_mems(text_record.text_id);
        cell.set_data(str, strlen(str));
      } else {
        cell.set_data(this->record_->data() + field_meta->offset(), field_meta->len());
      }
    }
    return RC::SUCCESS;
  }

  /**
   * @brief 根据spec的fieldExpr，获取某条record对应field的值
   * 目前只支持spec里存的Expression是fieldExpr
   * 由AggrFuncExpr的get_value或FieldExpr的get_value调用
   */
  RC find_cell(const TupleCellSpec &spec, Value &cell) const override
  {
    assert(spec.expression()->type() == ExprType::FIELD);
    FieldExpr  *spec_field_expr = (FieldExpr *)spec.expression();
    const char *table_name      = spec_field_expr->table_name();
    const char *table_alias     = spec_field_expr->table_alias();
    const char *field_name      = spec_field_expr->field_name();
//    std::cout << table_name << " " << table_alias << " " << table_alias_.c_str() << ":end" << endl;
    if (strlen(table_alias) == 0) {
      if (0 != strcmp(table_name, table_->name())) {
        return RC::NOTFOUND;
      }
    }
    else {
      if (0 != strcmp(table_alias, table_alias_.c_str())) {
        return RC::NOTFOUND;
      }
    }


    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = speces_[i];
      const Field     &field      = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        RC rc = cell_at(i, cell);
        return rc;
      }
    }
    return RC::NOTFOUND;
  }

#if 0
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
#endif

  Record &record() { return *record_; }

  const Record &record() const { return *record_; }

  void set_record(CompoundRecord &record) override
  {
    assert(record.size() >= 1);
    set_record(record.front());
    record.erase(record.begin());
  }

  void set_right_record(CompoundRecord &record) override
  {
    assert(!record.empty());
    set_record(record);
  }
  void get_record(CompoundRecord &record) const override { record.emplace_back(record_); }

private:
  common::Bitmap           bitmap_;
  Record                  *record_ = nullptr;
  const Table             *table_  = nullptr;
  string                   table_alias_;
  std::vector<FieldExpr *> speces_;
};


/**
 * @brief 从一行数据中，选择部分字段组成的元组，也就是投影操作
 *
 * @ingroup Tuple
 * @details 一般在select语句中使用。
 * 投影也可以是很复杂的操作，比如某些字段需要做类型转换、重命名、表达式运算、函数计算等。
 * 当前的实现是比较简单的，只是选择部分字段，不做任何其他操作。
 */
class ProjectTuple : public Tuple
{
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple) { this->tuple_ = tuple; }

  void add_cell_spec(TupleCellSpec *spec) { speces_.push_back(spec); }
  int  cell_num() const override { return speces_.size(); }

  /**
   * @brief 根据index，获取第i个投影列表达式的值
   * ProjectTuple是最顶层，由plain_communicator调用
   */
  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::INTERNAL;
    }
    if (tuple_ == nullptr) {
      return RC::INTERNAL;
    }

    const TupleCellSpec *spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  /**
   * 调用子tuple的find_cell，子tuple一般是row tuple或join tuple
   * 只有查询view时才可能调用，由aggr_expr和field_expr的get_value调用
   */
  RC find_cell(const TupleCellSpec &spec, Value &cell) const override {
    assert(spec.expression()->type() == ExprType::FIELD);
    FieldExpr* spec_field_expr = (FieldExpr*)spec.expression();
    assert(spec_field_expr->is_table() == false);
//    string spec_expr_name = spec_field_expr->to_string(false); // view的field_name，不需要加上view的名字
    for (TupleCellSpec* project_spec: speces_) {
//      string expr_name;
//      FieldExpr::gen_project_name(project_spec->expression(), true, expr_name); // 和创建view的select的投影列比较，这个投影列需要加上select的表名
      if (spec_field_expr->view_expr().get() == project_spec->expression()) {
        return project_spec->expression()->get_value(*tuple_, cell);
      }
//      if (spec_expr_name == expr_name) {
//        return project_spec->expression()->get_value(*tuple_, cell);
//      }

    }
    return RC::NOTFOUND;
  }

  void get_record(CompoundRecord &record) const override { tuple_->get_record(record); }

  void set_record(CompoundRecord &record) override { tuple_->set_record(record); }

  void set_right_record(CompoundRecord &record) override { tuple_->set_right_record(record); }

#if 0
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
#endif
private:
  std::vector<TupleCellSpec *> speces_;
  Tuple                       *tuple_ = nullptr;
};

class ExpressionTuple : public Tuple
{
public:
  ExpressionTuple(std::vector<std::unique_ptr<Expression>> &expressions) : expressions_(expressions) {}

  virtual ~ExpressionTuple() {}

  int cell_num() const override { return expressions_.size(); }

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(expressions_.size())) {
      return RC::INTERNAL;
    }

    const Expression *expr = expressions_[index].get();
    return expr->try_get_value(cell);
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell) const override
  {
    for (const std::unique_ptr<Expression> &expr : expressions_) {
      if (0 == strcmp(spec.alias(), expr->name().c_str())) {
        return expr->try_get_value(cell);
      }
    }
    return RC::NOTFOUND;
  }
  void set_record(CompoundRecord &record) override {}

  void set_right_record(CompoundRecord &record) override {}
  void get_record(CompoundRecord &record) const override {}

private:
  const std::vector<std::unique_ptr<Expression>> &expressions_;
};

/**
 * @brief 一些常量值组成的Tuple
 * @ingroup Tuple
 */
class ValueListTuple : public Tuple
{
public:
  ValueListTuple()          = default;
  virtual ~ValueListTuple() = default;

  void set_cells(const std::vector<Value> &cells) { cells_ = cells; }

  virtual int cell_num() const override { return static_cast<int>(cells_.size()); }

  virtual RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= cell_num()) {
      return RC::NOTFOUND;
    }

    cell = cells_[index];
    return RC::SUCCESS;
  }

  virtual RC find_cell(const TupleCellSpec &spec, Value &cell) const override { return RC::INTERNAL; }

  void set_record(CompoundRecord &record) override {}

  void set_right_record(CompoundRecord &record) override {}
  void get_record(CompoundRecord &record) const override {}

private:
  std::vector<Value> cells_;
};

/**
 * @brief 将两个tuple合并为一个tuple
 * @ingroup Tuple
 * @details 在join算子中使用
 */
class JoinedTuple : public Tuple
{
public:
  JoinedTuple()= default;
  JoinedTuple(Tuple *left, Tuple *right) : left_(left), right_(right) {};

  virtual ~JoinedTuple() = default;


  void set_left(Tuple *left) {
    left_ = left;
  }
  void set_right(Tuple *right) {
    right_ = right;
  }

  int cell_num() const override { return left_->cell_num() + right_->cell_num(); }

  /**
   * subQueryExpr获取第一列时调用
   */
  RC cell_at(int index, Value &value) const override
  {
    const int left_cell_num = left_->cell_num();
    if (index >= 0 && index < left_cell_num) {
      return left_->cell_at(index, value);
    }

    if (index >= left_cell_num && index < left_cell_num + right_->cell_num()) {
      return right_->cell_at(index - left_cell_num, value);
    }

    return RC::NOTFOUND;
  }

  /**
   * 由AggrFuncExpr的get_value或FieldExpr的get_value调用
   * 注意left_和right_的tuple都可以find的情况
   */
  RC find_cell(const TupleCellSpec &spec, Value &value) const override
  {
    RC rc = left_->find_cell(spec, value);
    if (rc == RC::SUCCESS || rc != RC::NOTFOUND) {
      return rc;
    }

    return right_->find_cell(spec, value);
  }
  void set_right_record(CompoundRecord &record) override
  {
    right_->set_right_record(record);
    assert(record.empty());
  }

  void set_record(CompoundRecord &record) override
  {
    left_->set_record(record);
    right_->set_record(record);
  }
  void get_record(CompoundRecord &record) const override
  {
    left_->get_record(record);
    right_->get_record(record);
  }

private:
  Tuple *left_  = nullptr;
  Tuple *right_ = nullptr;
};
/**
 * 在子查询中用于传父节点信息
 */
typedef JoinedTuple CompoundTuple;

class GroupTuple : public Tuple
{
public:
  GroupTuple(
      std::vector<std::unique_ptr<Expression>> &&aggr_exprs, std::vector<std::unique_ptr<Expression>> &&field_exprs,
      int num_project_aggr, int num_project_field)
      : aggr_exprs_(std::move(aggr_exprs)),  field_exprs_(std::move(field_exprs)),
        num_project_aggr_(num_project_aggr), num_project_field_(num_project_field)
  {
    aggr_counts_.resize(aggr_exprs_.size());
    aggr_all_null_.resize(aggr_exprs_.size());
    aggr_results_.resize(aggr_exprs_.size());
    field_results_.resize(field_exprs_.size());
  }

  virtual ~GroupTuple() {}

  void set_tuple(Tuple *tuple) { this->tuple_ = tuple; }

  int cell_num() const override { return tuple_->cell_num(); }

  RC cell_at(int index, Value &value) const override
  {
    if (tuple_ == nullptr) {
      return RC::EMPTY;
    }
    return tuple_->cell_at(index, value);
  }


  /**
   * @brief 根据spec的fieldExpr和aggr type，获取该field的aggr表达式的值
   * 目前只支持spec里存的Expression是fieldExpr
   * 由AggrFuncExpr的get_value或FieldExpr的get_value调用
   * 而上面这两用到GroupTuple的get_value，是由ProjectTuple的cell_at调用
   */
  RC find_cell(const TupleCellSpec &spec, Value &value) const override;

  void get_record(CompoundRecord &record) const override { tuple_->get_record(record); }

  void set_record(CompoundRecord &record) override { tuple_->set_record(record); }

  void set_right_record(CompoundRecord &record) override { tuple_->set_right_record(record); }

  RC do_aggregate_empty();

  void do_aggregate_first();

  void do_aggregate();

  void do_aggregate_done();

private:
  // sql执行顺序：record -> where -> group by -> order by -> having -> 投影
  // 所以group by需要记录having和投影的字段计算结果，不需要记录where的字段
  // 投影列和having的所有字段：
  std::vector<std::unique_ptr<Expression>> aggr_exprs_; // 聚集表达式的字段，需要group by操作
  std::vector<std::unique_ptr<Expression>> field_exprs_;   // 非聚集表达式的字段，需要group by操作
  int num_project_aggr_;  // 投影列中有多少聚集表达式，aggr_exprs_.size()减去它，剩下的就是having条件里的
  int num_project_field_;  // 投影列中有多少表达式

  std::vector<bool> aggr_all_null_; // 和aggr_exprs_一一对应
  std::vector<int>  aggr_counts_; // 和aggr_exprs_一一对应

  std::vector<Value> aggr_results_; // 和aggr_exprs_一一对应
  std::vector<Value> field_results_;  // 和field_exprs_一一对应

  Tuple *tuple_ = nullptr;   // 通常是table_scan的row_tuple

};