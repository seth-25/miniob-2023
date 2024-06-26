/**
* @brief 聚合表达式
* @ingroup Expression
*/
#include "sql/expr/expression.h"

class AggrFuncExpr : public Expression
{
public:
  AggrFuncExpr(AggrFuncType type, std::unique_ptr<Expression> field_expr, bool with_brace):
                                            aggr_type_(type), field_expr_(std::move(field_expr))
  {
    if (with_brace) {
      set_with_brace();
    }
  }
  AggrFuncExpr(AggrFuncType type, std::unique_ptr<Expression> field_expr, std::unique_ptr<Expression> value_expr, bool with_brace):
                aggr_type_(type), field_expr_(std::move(field_expr)), value_expr_(std::move(value_expr))
  {
    if (with_brace) {
      set_with_brace();
    }
    is_value_ = true;
  }
 virtual ~AggrFuncExpr() = default;

 ExprType type() const override { return ExprType::AGGRFUNC; }

 AttrType value_type() const override { return FLOATS; }

 RC get_value(const Tuple &tuple, Value &value) const override;

 AggrFuncType aggr_type() const { return aggr_type_; }

 std::unique_ptr<Expression> &field_expr() { return field_expr_; }

 std::unique_ptr<Expression> &value_expr() { return value_expr_; }

 bool is_param_value() { return is_value_; };

 std::string get_func_name() const;

 std::string to_string(bool with_table_name);

 static RC create_expression(const ExprSqlNode *expr, std::unique_ptr<Expression> &res_expr,
     const std::unordered_map<std::string, TableUnit*> &table_map, const TableUnit* default_table);

private:
  AggrFuncType aggr_type_;
  std::unique_ptr<Expression> field_expr_;
  std::unique_ptr<Expression> value_expr_;
  bool is_value_ = false;

};