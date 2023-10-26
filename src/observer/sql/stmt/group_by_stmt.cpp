
#include "group_by_stmt.h"
#include "sql/stmt/filter_stmt.h"


RC GroupByStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const std::vector<RelAttrSqlNode> &group_by_cols, std::vector<std::unique_ptr<Expression>> &aggr_exprs,
    std::vector<std::unique_ptr<Expression>> &field_exprs, GroupByStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = new GroupByStmt;
  stmt->aggr_exprs_ = std::move(aggr_exprs);
  stmt->field_exprs_ = std::move(field_exprs);
  for (auto & group_by_col : group_by_cols) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, group_by_col, table, field);
    std::unique_ptr<FieldExpr> expr(new FieldExpr(table, field));
    stmt->group_by_field_exprs_.emplace_back(std::move(expr));
  }


  // 检查group by 是否合法
  if (!stmt->aggr_exprs_.empty() && !stmt->field_exprs_.empty()) {  // 聚集和单个字段混合，根据题意，如果不是group by，返回fail
    if (stmt->group_by_field_exprs_.empty()) { // 不存在group by
      return RC::SQL_SYNTAX;
    }
    for (auto& field_expr : stmt->field_exprs_) {  // 投影和having中非聚集函数内的字段不在group by里
      bool in_group_by = false;
      std::vector<std::unique_ptr<FieldExpr>>&group_by_field_exprs = stmt->group_by_field_exprs_;
      for (auto& group_by_field_expr : group_by_field_exprs) {
        if (group_by_field_expr->field().equal( ((FieldExpr*)field_expr.get())->field() )) {
          in_group_by = true;
          break;
        }
      }
      if (!in_group_by) {
        return RC::SQL_SYNTAX;
      }
    }
  }
  return rc;
}
