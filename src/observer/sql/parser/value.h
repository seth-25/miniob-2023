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
// Created by Wangyunlai 2023/6/27
//

#pragma once

#include <string>

#define TEXT_MAX_LEN 65535

/**
 * @brief 属性的类型
 * 注意不少地方的范围判断依赖BOOLEANS、FLOATS等
 */
enum AttrType
{
  UNDEFINED,
  CHARS,          ///< 字符串类型
  INTS,           ///< 整数类型(4字节)
  DATES,          ///< 日期类型
  NULLS,          ///< null类型
  TEXTS,          ///< 变长类型
  FLOATS,         ///< 浮点数类型(4字节)
  BOOLEANS,       ///< boolean类型，当前不是由parser解析出来的，是程序内部使用的
};

const char *attr_type_to_string(AttrType type);
AttrType attr_type_from_string(const char *s);

/**
 * @brief 属性的值
 * 
 */
class Value 
{
public:

  Value(AttrType attr_type, char *data, int length = 4) : attr_type_(attr_type)
  {
    this->set_data(data, length);
  }
  explicit Value();
  explicit Value(int val);
  explicit Value(float val);
  explicit Value(bool val);
  explicit Value(const char *s, int len = 0);
  explicit Value(const char *y, const char *m, const char *d);

  Value(const Value &other) = default;
  Value &operator=(const Value &other) = default;

  void set_type(AttrType type)
  {
    this->attr_type_ = type;
  }
  void set_data(char *data, int length);
  void set_data(const char *data, int length)
  {
    this->set_data(const_cast<char *>(data), length);
  }
  void set_null();
  void set_int(int val);
  void set_float(float val);
  void set_boolean(bool val);
  void set_string(const char *s, int len = 0);
  void set_value(const Value &value);
  void set_date(const char *y, const char *m, const char *d);
  bool is_null() const;
  std::string to_string() const;

  int compare(const Value &other) const;
  static const Value& calc_min(const Value &left, const Value &right);
  static const Value& calc_max(const Value &left, const Value &right);
  static Value calc_add(const Value &left, const Value &right);
  static Value calc_div(const Value &left, const Value &right);

  const char *data() const;
  int length() const
  {
    return length_;
  }

  int text_length() const
  {
    return str_value_.length();
  }

  AttrType attr_type() const
  {
    return attr_type_;
  }

public:
  /**
   * 获取对应的值
   * 如果当前的类型与期望获取的类型不符，就会执行转换操作
   */
  int get_int() const;
  float get_float() const;
  std::string get_string() const;
  bool get_boolean() const;
  bool operator==(const Value &other) const
  {
    return 0 == compare(other);
  }

  bool operator!=(const Value &other) const
  {
    return 0 != compare(other);
  }

  bool operator<(const Value &other) const
  {
    return 0 > compare(other);
  }

  bool operator<=(const Value &other) const
  {
    return 0 >= compare(other);
  }

  bool operator>(const Value &other) const
  {
    return 0 < compare(other);
  }

  bool operator>=(const Value &other) const
  {
    return 0 <= compare(other);
  }

private:
  AttrType attr_type_ = UNDEFINED;
  int length_ = 0;

  union {
    int int_value_;
    float float_value_;
    bool bool_value_;
  } num_value_;
  std::string str_value_;
};

/**
 * text类型有关的方法
 */
struct TextHelper {
  static bool isInsertText(AttrType text_attr, AttrType char_attr) {
    return text_attr == TEXTS && char_attr == CHARS;
  }
};