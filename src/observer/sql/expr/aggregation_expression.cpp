#include "aggregation_expression.h"

RC AggrFuncExpr::create_expression(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, std::unique_ptr<Expression> &res_expr)
{
  assert(ExprSqlNodeType::AGGREGATION == expr->type);
  bool with_brace = expr->with_brace;
  AggrExprSqlNode* aggr_expr_node = expr->aggr_expr;
  if (ExprSqlNodeType::UNARY == aggr_expr_node->expr->type && 0 == aggr_expr_node->expr->unary_expr->is_attr) {
    // count(*) count(1) count(Value)
    assert(AggrFuncType::AGGR_COUNT == aggr_expr_node->type);
    std::unique_ptr<Expression> value_exp = nullptr;  // *或1用value表达式
    RC rc = Expression::create_expression(aggr_expr_node->expr, table_map, tables, value_exp);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("AggrFuncExpr Create Param Expression Failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
    assert(ExprType::VALUE == value_exp->type());
    std::unique_ptr<Expression> field_expr(new FieldExpr(tables[0], tables[0]->table_meta().field(1)));
    std::unique_ptr<AggrFuncExpr> aggr_func_expr(new AggrFuncExpr(
        AggrFuncType::AGGR_COUNT, std::move(field_expr), std::move(value_exp), with_brace));
    res_expr = std::move(aggr_func_expr);
    return RC::SUCCESS;
  }
  std::unique_ptr<Expression> param = nullptr;
  RC rc = Expression::create_expression(aggr_expr_node->expr, table_map, tables, param);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("AggrFuncExpr Create Param Expression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  assert(nullptr != param && ExprType::FIELD == param->type());
  std::unique_ptr<AggrFuncExpr> aggr_func_expr(new AggrFuncExpr(aggr_expr_node->type, std::move(param), with_brace));
  res_expr = std::move(aggr_func_expr);
  return RC::SUCCESS;
}

std::string AggrFuncExpr::get_func_name() const
{
  switch (aggr_type_) {
    case AggrFuncType::AGGR_MAX:
      return "max";
    case AggrFuncType::AGGR_MIN:
      return "min";
    case AggrFuncType::AGGR_SUM:
      return "sum";
    case AggrFuncType::AGGR_AVG:
      return "avg";
    case AggrFuncType::AGGR_COUNT:
      return "count";
    default:
      break;
  }
  return "unknown_aggr_fun";
}


RC AggrFuncExpr::get_value(const Tuple &tuple, Value &value) const { return RC::RECORD_EOF; } // todo
RC AggrFuncExpr::try_get_value(Value &value) const { return Expression::try_get_value(value); } // todo
