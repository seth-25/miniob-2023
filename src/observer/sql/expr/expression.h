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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <string.h>
#include <memory>
#include <string>

#include "storage/field/field.h"
#include "sql/parser/value.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "sql/stmt/select_stmt.h"

class Tuple;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType 
{
  NONE,
  STAR,         ///< 星号，表示所有字段
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  BINARY,       ///< 二元运算表达式
  FUNCTION,         ///< 函数
  AGGRFUNC,     ///< 聚合表达式
  SUBSQUERY,     ///< 子查询表达式
  VALUELIST,     ///< 多值的常量表达式
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression 
{
public:
  Expression() = default;
  virtual ~Expression() = default;

  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const
  {
    return RC::UNIMPLENMENT;
  }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string name() const { return name_; }
  virtual void set_name(std::string name) { name_ = name; }

  /**
   * 解析select投影和filter条件的复杂表达式
   * @return res_expr
   */
  static RC create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr,
      const std::unordered_map<std::string, TableUnit*> &table_map, const TableUnit* default_table,
      CompOp comp = NO_OP, Db *db = nullptr, Trx *trx = nullptr);
  /**
   * 解析select投影和having里的表达式，提取出field和aggregation
   * @return
   */
  static RC get_field_exprs(const ExprSqlNode *expr, std::vector<std::unique_ptr<Expression>> &field_exprs,
      const std::unordered_map<std::string, TableUnit *> &table_map, const TableUnit * default_table);
  static RC get_field_exprs_from_project(const Expression* expr, std::vector<std::unique_ptr<Expression>> &field_exprs);
  static RC get_aggr_exprs(const ExprSqlNode *expr, std::vector<std::unique_ptr<Expression>> &aggr_exprs,
      const std::unordered_map<std::string, TableUnit *> &table_map, const TableUnit *default_table);

  /**
   * 从表达式列表中找到名字一样的表达式
   * @return
   */
  static RC find_expr(std::vector<std::shared_ptr<Expression>>& exprs, std::shared_ptr<Expression>& res_expr, const std::string& find_expr_name, bool with_table_name);

  /**
   * 解析select投影表达式，设置列名
   * @return res_expr
   */
  static void gen_project_name(const Expression *expr, bool with_table_name, std::string &result_name, bool use_alias = true);

  void set_alias(const std::string &alias){
    alias_ = alias;
  }
  const std::string get_alias() const {
    return alias_;
  }

  void set_with_brace() { with_brace_ = true; }
  bool with_brace() const { return with_brace_; }

private:
  std::string name_;
  bool with_brace_ = false;
  std::string alias_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, string table_alias, const FieldMeta *field) : field_(table, field) {
    is_table_ = true;
    table_alias_ = std::move(table_alias);
  }
  FieldExpr(const Table *table, string table_alias, const FieldMeta *field, bool with_brace) : field_(table, field) {
    is_table_ = true;
    if (with_brace) {
      set_with_brace();
    }
    table_alias_ = std::move(table_alias);
  }
  FieldExpr(const Field &field, string table_alias) : field_(field) {
    is_table_ = true;
    table_alias_ = std::move(table_alias);
  }
  FieldExpr(std::shared_ptr<Expression> view_expr, std::string view_name) {
    is_table_ = false;
    view_expr_ = std::move(view_expr);
    view_name_ = std::move(view_name);
    gen_project_name(view_expr_.get(), false, view_field_name_);  // 不需要加上view的名字
    view_expr_value_type_ = view_expr_->value_type();
  }

  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override {
    if (is_table_) {
      return field_.attr_type();
    }
    else {
      return view_expr_value_type_;
    }
  }

  Field &field() {
    assert(is_table_);
    return field_;
  }

  const Field &field() const {
    assert(is_table_);
    return field_;
  }

  const char *table_name() const {
    if (is_table_) {
      return table_alias_.c_str();
    }
    else {
      return view_name_.c_str();
    }
  }

  const char * table_alias() const {
    assert(is_table_);
    return table_alias_.c_str();
  }

  const char *field_name() const {
    if (is_table_) {
      return field_.field_name();
    }
    else {
      return view_field_name_.c_str();
    }
  }

  RC get_value(const Tuple &tuple, Value &value) const override;

  std::string to_string(bool with_table_name) const;

  static RC create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr,
      const std::unordered_map<std::string, TableUnit*> &table_map, const TableUnit* default_table);

  bool with_aggr() const
  {
    return static_cast<int>(aggr_type_) >= 0 && aggr_type_ < AggrFuncType::UNDEFINED;
  }
  AggrFuncType get_aggr_type() const
  {
    assert(with_aggr());
    return aggr_type_;
  }
  void set_aggr(AggrFuncType type)
  {
    assert(static_cast<int>(type) >= 0 && type < AggrFuncType::UNDEFINED);
    this->aggr_type_ = type;
  }

  bool is_table() const {
    return is_table_;
  }

  std::shared_ptr<Expression> view_expr() {
      return view_expr_;
  }

  bool equal(FieldExpr* other) const {
    if (this->is_table() && other->is_table()) {
      return this->field_.equal(other->field());
    }
    else if (!this->is_table() && !other->is_table()){
      // todo 换成判断view_expr_
      return (this->view_name_ + "." + this->view_field_name_) == (other->view_name_ + "." + other->view_field_name_);
    }
    return false;
  }

  /**
   * 从表达式中获取对应的字段
   * @return res_expr
   */
//  static RC get_field_from_exprs(const Expression* expr, std::vector<Field> &fields);
  static RC get_field_expr_from_exprs(const Expression *expr, vector<FieldExpr*> &field_exprs);

  /**最上层输入为true
   * 是否是nullable的
   * @return res_expr
   */
  static RC get_field_isnull_from_exprs(const Expression* expr, bool &nullable);

private:
  bool is_table_ = false; // true使用field，false使view_expr
  Field field_;
  string table_alias_;

  std::shared_ptr<Expression> view_expr_;  // view的某列投影的表达式
  AttrType view_expr_value_type_;
  string view_name_;        // v
  string view_field_name_;   // t.id，包括原表的表名

  AggrFuncType aggr_type_ = AggrFuncType::UNDEFINED; // 用于AggrFunc的get_value(group tuple的)

};
