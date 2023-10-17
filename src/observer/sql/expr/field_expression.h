//#include "expression.h"
//
///**
// * @brief 字段表达式
// * @ingroup Expression
// */
//class FieldExpr : public Expression
//{
//public:
//  FieldExpr() = default;
//  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field)
//  {}
//  FieldExpr(const Field &field) : field_(field)
//  {}
//
//  virtual ~FieldExpr() = default;
//
//  ExprType type() const override { return ExprType::FIELD; }
//  AttrType value_type() const override { return field_.attr_type(); }
//
//  Field &field() { return field_; }
//
//  const Field &field() const { return field_; }
//
//  const char *table_name() const { return field_.table_name(); }
//
//  const char *field_name() const { return field_.field_name(); }
//
//  RC get_value(const Tuple &tuple, Value &value) const override;
//
//private:
//  Field field_;
//};