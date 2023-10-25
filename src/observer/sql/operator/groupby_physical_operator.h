#pragma once
#include "sql/expr/expression.h"
#include "sql/expr/aggregation_expression.h"
#include "physical_operator.h"

class GroupByPhysicalOperator: public PhysicalOperator
{
public:
  GroupByPhysicalOperator(
      std::vector<std::unique_ptr<FieldExpr>>&& group_by_field_exprs,
      std::vector<std::unique_ptr<Expression>>&& aggr_exprs,
      std::vector<std::unique_ptr<Expression>>&& field_exprs
      )
      : group_by_field_exprs_(std::move(group_by_field_exprs)),
        aggr_exprs_(std::move(aggr_exprs)),
        field_exprs_(std::move(field_exprs))
  {}

  PhysicalOperatorType type() const override {
    return PhysicalOperatorType::GROUP_BY;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;



private:
  std::vector<std::unique_ptr<FieldExpr>> group_by_field_exprs_; // 需要分组的字段

  // sql执行顺序：record -> where -> group by -> order by -> having -> 投影
  // 所以group by需要记录having和投影的字段计算结果，不需要记录where的字段
  // 投影列和having的所有字段：
  std::vector<std::unique_ptr<Expression>> aggr_exprs_; // 聚集表达式的字段
  std::vector<std::unique_ptr<Expression>> field_exprs_;   // 非聚集表达式的字段
};

