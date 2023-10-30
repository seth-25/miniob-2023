#include "expression.h"

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueListExpr : public Expression
{
public:
  explicit ValueListExpr(std::vector<Value>& values) : values_(values) {}

  virtual ~ValueListExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::UNIMPLENMENT; };
  RC try_get_value(Value &value) const override { return  RC::UNIMPLENMENT; };

  ExprType type() const override { return ExprType::VALUELIST; }

  AttrType value_type() const override { return UNDEFINED; };

  static RC create_expression(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, std::unique_ptr<Expression> &res_expr)
  {
    assert(expr->type == ExprSqlNodeType::VALUELIST);
    ValueListExprSqlNode* value_list_node = expr->value_list_expr;
    std::unique_ptr<Expression> value_list_expr (new ValueListExpr(value_list_node->values));
    res_expr = std::move(value_list_expr);
    return RC::SUCCESS;
  }

  const std::vector<Value>& get_values() const {
      return values_;
  };

private:
  std::vector<Value> values_;
};