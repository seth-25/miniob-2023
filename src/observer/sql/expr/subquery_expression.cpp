#include "subquery_expression.h"

RC SubQueryExpr::init() {
  std::vector<Field> fields;
  if (stmt_->project_expres().size() != 1) { // 子查询投影列只能是1列
    return RC::SQL_SYNTAX;
  }
  FieldExpr::get_field_from_exprs(stmt_->project_expres().front().get(), fields);
  if (fields.size() != 1) { // 子查询投影列只能是1列
    return RC::SQL_SYNTAX;
  }
  attr_type_ = fields[0].attr_type();
  return RC::SUCCESS;
}

RC SubQueryExpr::create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr,
    const std::unordered_map<std::string, TableUnit*> &table_map, CompOp comp, Db *db,
    Trx *trx)
{
  assert(expr->type == ExprSqlNodeType::SUBQUERY);
  Stmt *select_stmt = nullptr;
  RC rc = SelectStmt::create(db, trx, *expr->sub_query_expr->sub_select, table_map, select_stmt);
  if (RC::SUCCESS != rc) {
    LOG_ERROR("SubQueryExpression Create SelectStmt Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  assert(comp != NO_OP);
  switch (comp) {
    case EXISTS_OP:
    case NOT_EXISTS_OP:
      break;
    default: {  // 除了exists，其他的in、比较等操作都只支持1列
      if (((SelectStmt *)select_stmt)->project_expres().size() != 1) {
        return RC::SQL_SYNTAX;
      }
      break;
    }
  }
  SubQueryExpr* sub_query_expr = new SubQueryExpr((SelectStmt*) select_stmt, trx);
  sub_query_expr->init();
  std::unique_ptr<Expression> sub_expr (sub_query_expr);

  res_expr = std::move(sub_expr);
  return RC::SUCCESS;
}

RC SubQueryExpr::open_sub_query() const {
  assert(top_phy_oper_ != nullptr);
  return top_phy_oper_->open(trx_);
}

RC SubQueryExpr::close_sub_query() const {
  assert(top_phy_oper_ != nullptr);
  return top_phy_oper_->close();
}

// 只获取一行
RC SubQueryExpr::get_one_value(const Tuple &tuple, Value &value) const {
  assert(top_phy_oper_ != nullptr);
  top_phy_oper_->set_parent_tuple(&tuple);  // set parent tuple

  RC rc = top_phy_oper_->next();
  if (RC::RECORD_EOF == rc) {
    value.set_null();
  }
  if (RC::SUCCESS != rc) {
    return rc;
  }
  Tuple *child_tuple = top_phy_oper_->current_tuple();
  if (nullptr == child_tuple) {
    LOG_WARN("failed to get current record. rc=%s", strrc(rc));
    return RC::INTERNAL;
  }

  assert(child_tuple->cell_num() == 1); // 子查询只支持1列

  rc = child_tuple->cell_at(0, value);  // 只获取一行的第一列，子查询不支持多列和多行（没in any all some的情况）
  return rc;
}

/**
 * @return
 * 子查询1行都没有：RECORD_EOF
 * 子查询有且仅有1行：SUCCESS
 * 子查询超过1行：RECORD_EXIST
 */
RC SubQueryExpr::get_value(const Tuple &tuple, Value &value) const {
  open_sub_query();
  RC rc = get_one_value(tuple, value);
  if (RC::RECORD_EOF == rc) { // 子查询没有结果
    value.set_null();
  }
  else if (RC::SUCCESS == rc) {
    Value tmp_value;
    RC rc2 = get_one_value(tuple, tmp_value);  // 再获取一行
    if (RC::SUCCESS == rc2) {  // 子查询超过一行
      close_sub_query();
      return RC::RECORD_EXIST;
    }
  }
  close_sub_query();
  return rc;
}