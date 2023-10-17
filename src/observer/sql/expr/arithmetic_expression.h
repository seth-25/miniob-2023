#include "expression.h"

/**
* @brief 算术表达式
* @ingroup Expression
*/
class ArithmeticExpr : public Expression
{
public:
 enum class Type {
   ADD,
   SUB,
   MUL,
   DIV,
   NEGATIVE,
 };

public:
 ArithmeticExpr(Type type, Expression *left, Expression *right);
 ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
 virtual ~ArithmeticExpr() = default;

 ExprType type() const override { return ExprType::ARITHMETIC; }

 AttrType value_type() const override;

 RC get_value(const Tuple &tuple, Value &value) const override;
 RC try_get_value(Value &value) const override;

 Type arithmetic_type() const { return arithmetic_type_; }

 std::unique_ptr<Expression> &left() { return left_; }
 std::unique_ptr<Expression> &right() { return right_; }

private:
 RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

private:
 Type arithmetic_type_;
 std::unique_ptr<Expression> left_;
 std::unique_ptr<Expression> right_;
};