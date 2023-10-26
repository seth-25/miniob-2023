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
        tuple_(std::move(aggr_exprs), std::move(field_exprs))
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
  GroupTuple tuple_;

  bool is_first_ = true;  // 第一次运行
  bool is_new_group_ = true;  // 对列排序后，遇到的值是否是是新的group
  bool is_record_eof_ = false;  // 记录结束

  std::vector<Value> pre_values_; // 各个groupby的字段，上一个值，用于判断是否是新的group
};

