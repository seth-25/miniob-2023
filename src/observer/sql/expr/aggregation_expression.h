/**
* @brief 聚合表达式
* @ingroup Expression
*/
#include "expression.h"

class AggrFuncExpr : public Expression
{
public:
 enum class Type {
   MAX,
   MIN,
   COUNT,
   AVG,
   SUM,
 };

public:
  AggrFuncExpr(Type type, Expression *left, Expression *right);
  AggrFuncExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
 virtual ~AggrFuncExpr() = default;

 ExprType type() const override { return ExprType::AGGRFUNC; }

 AttrType value_type() const override;

 RC get_value(const Tuple &tuple, Value &value) const override;
 RC try_get_value(Value &value) const override;

 Type aggr_type() const { return aggr_type_; }

 std::unique_ptr<Expression> &left() { return left_; }
 std::unique_ptr<Expression> &right() { return right_; }

private:
 RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

private:
 Type aggr_type_;
 std::unique_ptr<Expression> left_;
 std::unique_ptr<Expression> right_;
};