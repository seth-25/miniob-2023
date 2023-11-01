#include "expression.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/stmt/select_stmt.h"
#include "sql/operator/project_logical_operator.h"

/**
 * @brief 函数表达式
 * @ingroup Expression
 */


class SubQueryExpr : public Expression
{

public:
  SubQueryExpr(SelectStmt* sub_query_stmt, Trx* trx): stmt_(sub_query_stmt), trx_(trx) {}

  virtual ~SubQueryExpr() = default;

  ExprType type() const override { return ExprType::SUBSQUERY; }

  AttrType value_type() const override { return attr_type_; };

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override { return RC::UNIMPLENMENT; };

  RC init();

  const SelectStmt * get_qub_query_stmt() const { return stmt_; };

  void set_log_oper(std::unique_ptr<LogicalOperator> &&sub_query_top_log_oper) {
    top_log_oper_ = std::move(sub_query_top_log_oper);
  }

  std::unique_ptr<LogicalOperator>& get_log_oper() {
    return top_log_oper_;
  }

  void set_phy_oper(std::unique_ptr<PhysicalOperator> &&sub_query_top_phy_oper) {
    top_phy_oper_ = std::move(sub_query_top_phy_oper);
  }

  static RC create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr,
      const std::unordered_map<std::string, Table *> &table_map, CompOp comp, Db *db, Trx *trx);

  RC open_sub_query() const;

  RC close_sub_query() const;

  RC get_one_value(const Tuple &tuple, Value &value) const;

private:
  SelectStmt *stmt_ = nullptr;  // select stmt
  std::unique_ptr<LogicalOperator>  top_log_oper_ = nullptr; // project logical oper
  std::unique_ptr<PhysicalOperator> top_phy_oper_ = nullptr;  // project physical oper
  Trx* trx_;
  AttrType attr_type_;
};