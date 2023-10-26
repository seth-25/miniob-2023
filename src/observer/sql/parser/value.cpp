/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2023/06/28.
//

#include <sstream>
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/lang/typecast.h"

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "dates", "nulls", "floats", "booleans"};

const char *attr_type_to_string(AttrType type)
{
  assert(type!=NULLS);
  if (type >= UNDEFINED && type <= FLOATS) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}
Value::Value()
{
  set_null();
}

Value::Value(int val)
{
  set_int(val);
}

Value::Value(float val)
{
  set_float(val);
}

Value::Value(bool val)
{
  set_boolean(val);
}

Value::Value(const char *s, int len /*= 0*/)
{
  set_string(s, len);
}

Value::Value(const char *y, const char *m, const char *d)
{
  set_date(y, m, d);
}

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case DATES:
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_ = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_ = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_ = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_null()
{
  attr_type_ = AttrType::NULLS;
}
void Value::set_int(int val)
{
  attr_type_ = INTS;
  num_value_.int_value_ = val;
  length_ = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_ = FLOATS;
  num_value_.float_value_ = val;
  length_ = sizeof(val);
}
void Value::set_boolean(bool val)
{
  attr_type_ = BOOLEANS;
  num_value_.bool_value_ = val;
  length_ = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_date(const char *year, const char *month, const char *day)
{
  attr_type_ = DATES;
  int y, m, d;
  y = atoi(year);
  m = atoi(month);
  d = atoi(day);
  static int mon_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool leap = (y%400==0 || (y%100 && y%4==0));
  if( y > 0
         && (m > 0)&&(m <= 12)
         && (d > 0)&&(d <= ((m==2 && leap)?1:0) + mon_days[m]) ) {
    num_value_.int_value_ = 10000 * y + m * 100 + d;  // 转化后的值存在int_value
  }
  else {
    attr_type_ = UNDEFINED;
  }
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case DATES:
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case CHARS: {
      return str_value_.c_str();
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case DATES: {
      int y = num_value_.int_value_ / 10000;
      int m = (num_value_.int_value_ - y * 10000) / 100;
      int d = num_value_.int_value_ - y * 10000 - m * 100;
      os << y << "-" << (m < 10 ? "0" : "") << m << "-" << (d < 10 ? "0" : "") << d;
    } break;
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case NULLS: {
      os << "NULL";
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::compare(const Value &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case DATES:  // date的值转化后存在int里，比较直接复用int的比较
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == CHARS || other.attr_type_ == CHARS) {
    // char与int或float比较，将双方都转成float
    // todo 只支持char与int float比较，不支持char与date等其他属性
    void *p_left = nullptr;
    if (this->attr_type_ == INTS || this->attr_type_ == CHARS) {
      p_left = (void *)common::type_cast_to[this->attr_type_][FLOATS](this->data());
    }
    else if (this->attr_type_ == FLOATS) {
      p_left = (void *)this->data();
    }

    void *p_right = nullptr;
    if (other.attr_type_ == INTS || other.attr_type_ == CHARS) {
      p_right = (void *)common::type_cast_to[other.attr_type_][FLOATS](other.data());
    }
    else if (other.attr_type_ == FLOATS) {
      p_right = (void *)other.data();
    }
    if (p_left == nullptr || p_right == nullptr) {
      LOG_WARN("not supported compare type");
      return -1;  // TODO return rc?
    }
    return common::compare_float(p_left, p_right);
  }
    else if ((this->attr_type_ == INTS || this->attr_type_ == FLOATS) && other.attr_type_ == CHARS) {
    void * p_float = (float *)common::type_cast_to[other.attr_type_][FLOATS](other.data());
    return common::compare_float((void *)this->data(), p_float);
  }

  LOG_WARN("not supported compare type");
  return -1;  // TODO return rc?
}
const Value& Value::calc_min(const Value &left, const Value &right) {
  if (left.is_null()) {
    return right;
  }
  return left > right ? right : left;
}

const Value& Value::calc_max(const Value &left, const Value &right) {
  if (left.is_null()) {
    return right;
  }
  return left > right ? left : right;
}

Value Value::calc_add(const Value &left, const Value &right) {
  Value result_value;
  if (left.is_null() || right.is_null()) {
    result_value.set_null();
    return result_value;
  }
  if (left.attr_type_ == INTS && right.attr_type_ == INTS) {
    int result = left.get_int() + right.get_int();
    result_value.set_int(result);
  }
  else {
    float *left_float = (float *)common::type_cast_to[left.attr_type_][FLOATS](left.data());
    float *right_float = (float *)common::type_cast_to[right.attr_type_][FLOATS](right.data());
    assert(nullptr != left_float);
    assert(nullptr != right_float);
    float  result = *left_float + *right_float;
    result_value.set_float(result);
    free(left_float);
    free(right_float);
  }
  return result_value;
}

Value Value::calc_div(const Value &left, const Value &right) {
  Value result_value;
  if (left.is_null() || right.is_null()) {
    result_value.set_null();
    return result_value;
  }
  float *left_float = (float *)common::type_cast_to[left.attr_type_][FLOATS](left.data());
  float *right_float = (float *)common::type_cast_to[right.attr_type_][FLOATS](right.data());
  assert(nullptr != left_float);
  assert(nullptr != right_float);
  if (abs(*right_float) < 1e-6) {
    result_value.set_type(AttrType::NULLS);
  } else {
    float result = *left_float / *right_float;
    result_value.set_float(result);
  }
  free(left_float);
  free(right_float);
  return result_value;
}

int Value::get_int() const  // TODO 考虑DATES
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const  // TODO 考虑DATES
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}
bool Value::is_null() const
{
  return AttrType::NULLS == attr_type_;
}

std::string Value::get_string() const
{
  return this->to_string();
}

bool Value::get_boolean() const  // TODO 考虑DATES
{
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}
