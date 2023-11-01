#include "expression.h"

/**
* @brief 二元表达式
* @ingroup Expression
 */
class BinaryExpression : public Expression
{

public:
//  BinaryExpression(ExprOp op, Expression *left, Expression *right) : op_(op), left_(left), right_(right) {}
  BinaryExpression(ExprOp op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right , bool with_brace, bool is_minus)
      : op_(op), left_(std::move(left)), right_(std::move(right)), is_minus_(is_minus)
  {
    if (with_brace) {
      set_with_brace();
    }
  }
//  BinaryExpression(ExprOp op, Expression *left, Expression *right, bool with_brace, bool is_minus)
//      : op_(op), left_(left), right_(right), is_minus_(is_minus)
//  {
//    if (with_brace) {
//      set_with_brace();
//    }
//  }
  virtual ~BinaryExpression() = default;

  ExprType type() const override { return ExprType::BINARY; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  ExprOp op() const { return op_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  static RC  create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr,
       const std::unordered_map<std::string, Table *> &table_map, const Table* default_table);
  bool is_minus() const { return is_minus_; }
  const char get_op_char() const;
private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;
private:
  ExprOp op_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
  bool is_minus_ = false;  // 打印用
};