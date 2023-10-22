#include "expression.h"

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression
{
public:
 ValueExpr() = default;
 explicit ValueExpr(const Value &value) : value_(value) {}
 explicit ValueExpr(const Value &value, bool with_brace) : value_(value) {
   if (with_brace) {
     set_with_brace();
   }
 }

 virtual ~ValueExpr() = default;

 RC get_value(const Tuple &tuple, Value &value) const override;
 RC try_get_value(Value &value) const override { value = value_; return RC::SUCCESS; }

 ExprType type() const override { return ExprType::VALUE; }

 AttrType value_type() const override { return value_.attr_type(); }

 void get_value(Value &value) const { value = value_; }

 const Value &get_value() const { return value_; }

 std::string to_string() const;

 static RC create_expression(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
     const std::vector<Table *> &tables, std::unique_ptr<Expression> &res_expr);

private:
 Value value_;
};