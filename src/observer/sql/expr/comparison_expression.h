#include "expression.h"

/**
* @brief 比较表达式
* @ingroup Expression
*/
class ComparisonExpr : public Expression
{
public:
 ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
 virtual ~ComparisonExpr();

 ExprType type() const override { return ExprType::COMPARISON; }

 RC get_value(const Tuple &tuple, Value &value) const override;

 AttrType value_type() const override { return BOOLEANS; }

 CompOp comp() const { return comp_; }

 std::unique_ptr<Expression> &left()  { return left_;  }
 std::unique_ptr<Expression> &right() { return right_; }

 /**
  * 尝试在没有tuple的情况下获取当前表达式的值
  * 在优化的时候，可能会使用到
  * left和right都是值的话，提前算出来
  */
 RC try_get_value(Value &value) const override;

 /**
  * compare the two tuple cells
  * @param value the result of comparison
  */
 RC compare_value(const Value &left, const Value &right, bool &value) const;

private:
 CompOp comp_;
 std::unique_ptr<Expression> left_;
 std::unique_ptr<Expression> right_;
};