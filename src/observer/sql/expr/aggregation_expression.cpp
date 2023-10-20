//
// Created by seth on 2023/10/16.
//

#include "aggregation_expression.h"

AggrFuncExpression::AggrFuncExpression(AggrFuncExpression::Type type, Expression *expr)
    : aggr_type_(type), expr_(expr)
{}
RC AggrFuncExpression::get_value(const Tuple &tuple, Value &value) const { return RC::RECORD_EOF; } // todo
RC AggrFuncExpression::try_get_value(Value &value) const { return Expression::try_get_value(value); } // todo
