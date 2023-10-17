#include "expression.h"

/**
* @brief 类型转换表达式
* @ingroup Expression
*/
class CastExpr : public Expression
{
public:
 CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
 virtual ~CastExpr();

 ExprType type() const override
 {
   return ExprType::CAST;
 }
 RC get_value(const Tuple &tuple, Value &value) const override;

 RC try_get_value(Value &value) const override;

 AttrType value_type() const override { return cast_type_; }

 std::unique_ptr<Expression> &child() { return child_; }

private:
 RC cast(const Value &value, Value &cast_value) const;

private:
 std::unique_ptr<Expression> child_;  ///< 从这个表达式转换
 AttrType cast_type_;  ///< 想要转换成这个类型
};