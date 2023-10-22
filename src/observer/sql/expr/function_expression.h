#include "expression.h"

/**
* @brief 函数表达式
* @ingroup Expression
 */


class FuncExpression : public Expression
{

public:
  FuncExpression(FuncType func_type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, bool with_brace)
      : func_type_(func_type), left_(std::move(left)), right_(std::move(right)) {
    if (with_brace) {
      set_with_brace();
    }
  }

  virtual ~FuncExpression() = default;

  ExprType type() const override { return ExprType::FUNCTION; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  FuncType get_func_type() const { return func_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  static RC create_expression(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, std::unique_ptr<Expression> &res_expr);
private:
  RC calc_func_length_value(const Tuple &tuple, Value &value) const;
  RC calc_func_round_value(const Tuple &tuple, Value &value) const;
  RC calc_func_data_format_value(const Tuple &tuple, Value &value) const;
private:
  FuncType func_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};