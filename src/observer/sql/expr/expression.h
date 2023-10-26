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
  static RC create_expression(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, std::unique_ptr<Expression> &res_expr);
  /**
   * 解析select投影和having里的表达式，提取出field和aggregation
   * @return
   */
  static RC get_field_exprs(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, std::vector<std::unique_ptr<Expression>> &field_exprs);
  static RC get_aggr_exprs(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, std::vector<std::unique_ptr<Expression>> &aggr_exprs);

  /**
   * 解析select投影表达式，设置列名
   * @return res_expr
   */
  static void gen_project_name(const Expression *expr, bool with_table_name, std::string &result_name);

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
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Table *table, const FieldMeta *field, bool with_brace) : field_(table, field) {
    if (with_brace) {
      set_with_brace();
    }
  }
  FieldExpr(const Field &field) : field_(field)
  {}

  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }

  const char *field_name() const { return field_.field_name(); }

  RC get_value(const Tuple &tuple, Value &value) const override;

  std::string to_string(bool with_table_name) const;

  static RC create_expression(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, std::unique_ptr<Expression> &res_expr);


  bool with_aggr() const
  {
    return static_cast<int>(aggr_type_) >= 0 && aggr_type_ < AggrFuncType::AGGR_FUNC_TYPE_NUM;
  }
  AggrFuncType get_aggr_type() const
  {
    assert(with_aggr());
    return aggr_type_;
  }
  void set_aggr(AggrFuncType type)
  {
    assert(static_cast<int>(type) >= 0 && type < AggrFuncType::AGGR_FUNC_TYPE_NUM);
    this->aggr_type_ = type;
  }
//  /**
//   * 从表达式中获取对应的字段
//   * @return res_expr
//   */
//  static RC get_field_from_exprs(const Expression* expr, std::vector<Field> &fields);

private:
  Field field_;

  AggrFuncType aggr_type_ = AggrFuncType::AGGR_FUNC_TYPE_NUM; // 用于AggrFunc的get_value(group tuple的)
};



/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
//class ValueExpr;
//class ValueExpr : public Expression
//{
//public:
//  ValueExpr() = default;
//  explicit ValueExpr(const Value &value) : value_(value)
//  {}
//
//  virtual ~ValueExpr() = default;
//
//  RC get_value(const Tuple &tuple, Value &value) const override;
//  RC try_get_value(Value &value) const override { value = value_; return RC::SUCCESS; }
//
//  ExprType type() const override { return ExprType::VALUE; }
//
//  AttrType value_type() const override { return value_.attr_type(); }
//
//  void get_value(Value &value) const { value = value_; }
//
//  const Value &get_value() const { return value_; }
//
//private:
//  Value value_;
//};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
//class CastExpr;
//class CastExpr : public Expression
//{
//public:
//  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
//  virtual ~CastExpr();
//
//  ExprType type() const override
//  {
//    return ExprType::CAST;
//  }
//  RC get_value(const Tuple &tuple, Value &value) const override;
//
//  RC try_get_value(Value &value) const override;
//
//  AttrType value_type() const override { return cast_type_; }
//
//  std::unique_ptr<Expression> &child() { return child_; }
//
//private:
//  RC cast(const Value &value, Value &cast_value) const;
//
//private:
//  std::unique_ptr<Expression> child_;  ///< 从这个表达式转换
//  AttrType cast_type_;  ///< 想要转换成这个类型
//};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
//class ComparisonExpr;
//class ComparisonExpr : public Expression
//{
//public:
//  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
//  virtual ~ComparisonExpr();
//
//  ExprType type() const override { return ExprType::COMPARISON; }
//
//  RC get_value(const Tuple &tuple, Value &value) const override;
//
//  AttrType value_type() const override { return BOOLEANS; }
//
//  CompOp comp() const { return comp_; }
//
//  std::unique_ptr<Expression> &left()  { return left_;  }
//  std::unique_ptr<Expression> &right() { return right_; }
//
//  /**
//   * 尝试在没有tuple的情况下获取当前表达式的值
//   * 在优化的时候，可能会使用到
//   */
//  RC try_get_value(Value &value) const override;
//
//  /**
//   * compare the two tuple cells
//   * @param value the result of comparison
//   */
//  RC compare_value(const Value &left, const Value &right, bool &value) const;
//
//private:
//  CompOp comp_;
//  std::unique_ptr<Expression> left_;
//  std::unique_ptr<Expression> right_;
//};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
//class ConjunctionExpr;
//class ConjunctionExpr : public Expression
//{
//public:
//  enum class Type {
//    AND,
//    OR,
//  };
//
//public:
//  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
//  virtual ~ConjunctionExpr() = default;
//
//  ExprType type() const override { return ExprType::CONJUNCTION; }
//
//  AttrType value_type() const override { return BOOLEANS; }
//
//  RC get_value(const Tuple &tuple, Value &value) const override;
//
//  Type conjunction_type() const { return conjunction_type_; }
//
//  std::vector<std::unique_ptr<Expression>> &children() { return children_; }
//
//private:
//  Type conjunction_type_;
//  std::vector<std::unique_ptr<Expression>> children_;
//};


/**
 * @brief 算术表达式
 * @ingroup Expression
 */
//class ArithmeticExpr;
///**
// * @brief 算术表达式
// * @ingroup Expression
// */
//class ArithmeticExpr : public Expression
//{
//public:
//  enum class Type {
//    ADD,
//    SUB,
//    MUL,
//    DIV,
//    NEGATIVE,
//  };
//
//public:
//  ArithmeticExpr(Type type, Expression *left, Expression *right);
//  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
//  virtual ~ArithmeticExpr() = default;
//
//  ExprType type() const override { return ExprType::ARITHMETIC; }
//
//  AttrType value_type() const override;
//
//  RC get_value(const Tuple &tuple, Value &value) const override;
//  RC try_get_value(Value &value) const override;
//
//  Type arithmetic_type() const { return arithmetic_type_; }
//
//  std::unique_ptr<Expression> &left() { return left_; }
//  std::unique_ptr<Expression> &right() { return right_; }
//
//private:
//  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;
//
//private:
//  Type arithmetic_type_;
//  std::unique_ptr<Expression> left_;
//  std::unique_ptr<Expression> right_;
//};
