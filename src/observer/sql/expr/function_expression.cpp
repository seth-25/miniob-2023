#include <iomanip>
#include "function_expression.h"

RC FuncExpression::calc_func_length_value(const Tuple &tuple, Value &value) const
{
  Value param_value;  // 函数参数
  left_->get_value(tuple, param_value);
  if (param_value.attr_type() != CHARS) {
    LOG_WARN("FuncExpression length unsupported type");
    return RC::NOTFOUND;
  }
  value.set_int((int)strlen(param_value.data()));
  return RC::SUCCESS;
}

RC FuncExpression::calc_func_round_value(const Tuple &tuple, Value &value) const
{
  if (right_ != nullptr) {
    Value param_value;  // 函数参数
    Value param_precision_value;  // 函数精度
    left_->get_value(tuple, param_value);
    right_->get_value(tuple, param_precision_value);
    if (param_value.attr_type() != FLOATS) {
      LOG_WARN("FuncExpression round unsupported type");
      return RC::NOTFOUND;
    }
    if (param_precision_value.attr_type() != INTS) {
      LOG_WARN("FuncExpression round unsupported type");
      return RC::NOTFOUND;
    }
    float ans_float = param_value.get_float();
    int ans_precision = param_precision_value.get_int();
    auto inner_round = [](float f, int precision) {
      std::stringstream ss;
      ss << std::fixed << std::setprecision(precision) << f;
      ss >> f;
      return f;
    };
    *(uint32_t *)&ans_float += 1;
    ans_float = inner_round(ans_float, ans_precision);
    value.set_float(ans_float);
  } else {
    Value param_value;
    left_->get_value(tuple, param_value);
    if (param_value.attr_type() != FLOATS) {
      LOG_WARN("FuncExpression round unsupported type");
      return RC::INTERNAL;
    }
    float ans_float = param_value.get_float();
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << ans_float;
    ss >> ans_float;
    value.set_float(ans_float);
  }
  return RC::SUCCESS;
}

RC FuncExpression::calc_func_data_format_value(const Tuple &tuple, Value &value) const
{
  Value date_value;
  Value format_value;
  left_->get_value(tuple, date_value);
  right_->get_value(tuple, format_value);
  if (date_value.attr_type() != DATES) {
    LOG_WARN("FuncExpression data format unsupported type");
    return RC::INTERNAL;
  }
  if (format_value.attr_type() != CHARS) {
    LOG_WARN("FuncExpression data format unsupported type");
    return RC::INTERNAL;
  }
  int cell_date = *(int *)(date_value.data());
  char *cell_format_chars = (char *)(format_value.data());
  std::string result_date_str;
  int year = cell_date / 10000;
  int month = (cell_date / 100) % 100;
  int day = cell_date % 100;
  for (size_t i = 0; i < strlen(cell_format_chars); i++) {
    // A ~ z
    if (65 <= cell_format_chars[i] && cell_format_chars[i] <= 122) {
      switch (cell_format_chars[i]) {
        case 'Y': {
          char tmp[5];
          sprintf(tmp, "%d", year);
          result_date_str += tmp;
          break;
        }
        case 'y': {
          char tmp[5];
          sprintf(tmp, "%d", year % 100);
          if (0 <= (year % 100) && (year % 100) <= 9) {
            result_date_str += "0";
          }
          result_date_str += tmp;
          break;
        }
        case 'M': {
          switch (month) {
            case 1: {
              result_date_str += "January";
              break;
            }
            case 2: {
              result_date_str += "February";
              break;
            }
            case 3: {
              result_date_str += "March";
              break;
            }
            case 4: {
              result_date_str += "April";
              break;
            }
            case 5: {
              result_date_str += "May";
              break;
            }
            case 6: {
              result_date_str += "June";
              break;
            }
            case 7: {
              result_date_str += "July";
              break;
            }
            case 8: {
              result_date_str += "August";
              break;
            }
            case 9: {
              result_date_str += "September";
              break;
            }
            case 10: {
              result_date_str += "October";
              break;
            }
            case 11: {
              result_date_str += "November";
              break;
            }
            case 12: {
              result_date_str += "December";
              break;
            }
            default: {
              return RC::INTERNAL;
              break;
            }
          }
          break;
        }
        case 'm': {
          char tmp[3];
          sprintf(tmp, "%d", month);
          if (0 <= month && month <= 9) {
            result_date_str += "0";
          }
          result_date_str += tmp;
          break;
        }
        case 'D': {
          char tmp[3];
          sprintf(tmp, "%d", day);
          if (10 <= day && day <= 20) {
            result_date_str += tmp;
            result_date_str += "th";
          } else {
            switch (day % 10) {
              case 1: {
                result_date_str += tmp;
                result_date_str += "st";
                break;
              }
              case 2: {
                result_date_str += tmp;
                result_date_str += "nd";
                break;
              }
              case 3: {
                result_date_str += tmp;
                result_date_str += "rd";
                break;
              }
              default: {
                result_date_str += tmp;
                result_date_str += "th";
                break;
              }
            }
          }
          break;
        }
        case 'd': {
          char tmp[3];
          sprintf(tmp, "%d", day);
          if (0 <= day && day <= 9) {
            result_date_str += "0";
          }
          result_date_str += tmp;
          break;
        }
        default: {
          result_date_str += cell_format_chars[i];
          break;
        }
      }
    } else if (cell_format_chars[i] != '%') {
      result_date_str += cell_format_chars[i];
    }
  }
  value.set_string(strdup(result_date_str.c_str()), (int)strlen(result_date_str.c_str()));
  return RC::SUCCESS;
}


RC FuncExpression::get_value(const Tuple &tuple, Value &value) const
{
  RC rc;
  switch (func_type_) {
    case FuncType::FUNC_LENGTH: {
      rc = calc_func_length_value(tuple, value);
      break;
    }
    case FuncType::FUNC_ROUND: {
      rc = calc_func_round_value(tuple, value);
      break;
    }
    case FuncType::FUNC_DATE_FORMAT: {
      rc = calc_func_data_format_value(tuple, value);
      break;
    }
    default:
      rc = RC::NOTFOUND;
      break;
  }
  return rc;
}

RC FuncExpression::create_expression(const ExprSqlNode *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, std::unique_ptr<Expression> &res_expr)
{
  RC rc = RC::SUCCESS;
  std::unique_ptr<Expression> left = nullptr;
  std::unique_ptr<Expression> right = nullptr;
  FuncExprSqlNode*func_expr_node = expr->func_expr;
  switch (func_expr_node->type) {
    case FuncType::FUNC_LENGTH: {
      rc = Expression::create_expression(func_expr_node->exprs[0], table_map, tables, left);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("FuncExpression LENGTH Create Param[0] Failed. RC = %d:%s", rc, strrc(rc));
        return rc;
      }
      break;
    }
    case FuncType::FUNC_ROUND: {
      rc = Expression::create_expression(func_expr_node->exprs[0], table_map, tables, left);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("FuncExpression ROUND Create Param[0] Failed. RC = %d:%s", rc, strrc(rc));
        return rc;
      }
      if (func_expr_node->exprs.size() == 2) {
        rc = Expression::create_expression(func_expr_node->exprs[1], table_map, tables, right);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("FuncExpression ROUND Create Param[1] Failed. RC = %d:%s", rc, strrc(rc));
          return rc;
        }
      }
      break;
    }
    case FuncType::FUNC_DATE_FORMAT: {
      rc = Expression::create_expression(func_expr_node->exprs[0], table_map, tables, left);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("FuncExpression DATE_FORMAT Create Param[0] Failed. RC = %d:%s", rc, strrc(rc));
        return rc;
      }
      rc = Expression::create_expression(func_expr_node->exprs[1], table_map, tables, right);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("FuncExpression DATE_FORMAT Create Param[1] Failed. RC = %d:%s", rc, strrc(rc));
        return rc;
      }
      break;
    }
    default:
      return RC::NOTFOUND;
      break;
  }
  std::unique_ptr<FuncExpression> func_expr(new FuncExpression(func_expr_node->type, std::move(left), std::move(right), false));

  res_expr = std::move(func_expr);
  return rc;
}
AttrType FuncExpression::value_type() const {
  switch (func_type_) {
    case FuncType::FUNC_LENGTH: {
      return INTS;
    }
    break;
    case FuncType::FUNC_ROUND: {
      return FLOATS;
    } break;
    case FuncType::FUNC_DATE_FORMAT: {
      return CHARS;
    } break;
  }
  return UNDEFINED;
}
RC FuncExpression::try_get_value(Value &value) const {
  LOG_WARN("没实现binary expression的try to get value");
  RC rc = RC::INTERNAL;
  return rc;
}
