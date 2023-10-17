#include "expression.h"

/**
* @brief 联结表达式
* @ingroup Expression
* 多个表达式使用同一种关系(AND或OR)来联结
* 当前miniob仅有AND操作
*/
class ConjunctionExpr : public Expression
{
public:
 enum class Type {
   AND,
   OR,
 };

public:
 ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
 virtual ~ConjunctionExpr() = default;

 ExprType type() const override { return ExprType::CONJUNCTION; }

 AttrType value_type() const override { return BOOLEANS; }

 RC get_value(const Tuple &tuple, Value &value) const override;

 Type conjunction_type() const { return conjunction_type_; }

 std::vector<std::unique_ptr<Expression>> &children() { return children_; }

private:
 Type conjunction_type_;
 std::vector<std::unique_ptr<Expression>> children_;
};