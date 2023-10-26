#pragma once


#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "sql/expr/expression.h"

/**
 * @brief 记录group by 表达式后面的字段fieldExpr
 * @ingroup Statement
 */
class GroupByStmt : public Stmt
{
public:
  GroupByStmt() = default;
  ~GroupByStmt() override {
    group_by_field_exprs_.clear();
    field_exprs_.clear();
    aggr_exprs_.clear();
  }
  StmtType type() const override
  {
    return StmtType::GROUP_BY;
  }
  std::vector<std::unique_ptr<FieldExpr>>&group_by_field_exprs() {
    return group_by_field_exprs_;
  }
  std::vector<std::unique_ptr<Expression>>&aggr_exprs() {
    return aggr_exprs_;
  }
  std::vector<std::unique_ptr<Expression>>&field_exprs() {
    return field_exprs_;
  }
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const std::vector<RelAttrSqlNode>& group_by_cols,
      std::vector<std::unique_ptr<Expression>>& aggr_expr,
      std::vector<std::unique_ptr<Expression>>& field_expr,
      GroupByStmt *&stmt);

private:
  std::vector<std::unique_ptr<FieldExpr>> group_by_field_exprs_; // 需要分组的字段

  // sql执行顺序：record -> where -> group by -> order by -> having -> 投影
  // 所以group by后面需要记录having和投影的字段计算结果，不需要记录where的字段
  // 投影列和having的所有字段：
  std::vector<std::unique_ptr<Expression>> aggr_exprs_; // 聚集表达式的字段
  std::vector<std::unique_ptr<Expression>> field_exprs_;   // 非聚集表达式的字段
};
