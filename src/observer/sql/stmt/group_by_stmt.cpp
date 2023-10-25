
#include "group_by_stmt.h"
#include "sql/stmt/filter_stmt.h"


RC GroupByStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const std::vector<RelAttrSqlNode> &group_by_cols, std::vector<std::unique_ptr<Expression>> &aggr_expr,
    std::vector<std::unique_ptr<Expression>> &field_expr, GroupByStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = new GroupByStmt;
  stmt->aggr_exprs_ = std::move(aggr_expr);
  stmt->field_exprs_ = std::move(field_expr);

  for (auto & group_by_col : group_by_cols) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, group_by_col, table, field);
    std::unique_ptr<FieldExpr> expr(new FieldExpr(table, field));
    stmt->group_by_field_exprs_.emplace_back(std::move(expr));
  }
  return rc;
}
