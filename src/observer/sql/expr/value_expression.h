#include "expression.h"

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression
{
public:
 ValueExpr() = default;
 explicit ValueExpr(const Value &value) : value_(value)
 {}

 virtual ~ValueExpr() = default;

 RC get_value(const Tuple &tuple, Value &value) const override;
 RC try_get_value(Value &value) const override { value = value_; return RC::SUCCESS; }

 ExprType type() const override { return ExprType::VALUE; }

 AttrType value_type() const override { return value_.attr_type(); }

 void get_value(Value &value) const { value = value_; }

 const Value &get_value() const { return value_; }

private:
 Value value_;
};