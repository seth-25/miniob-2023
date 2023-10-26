//
// Created by seth on 2023/10/9.
//

#pragma once

#include "src/observer/sql/parser/value.h"
namespace common {

typedef char *(*cast_func_ptr)(const char *);  // char* (*) (const char*) 的函数指针


/**
 * 检查value_type是否能转化成field_type
 * @param x value_type
 * @param y field_type
 * @return
 */
bool type_cast_check(AttrType x, AttrType y);

/**
 * 返回x转化成y的参数
 * 例如type_cast_to[CHARS][INTS] 就是返回char_to_int
 */
extern cast_func_ptr type_cast_to[AttrType::BOOLEANS + 1][AttrType::BOOLEANS + 1];


char *char_to_int(const char *value_data);
char *char_to_float(const char *value_data);
char *int_to_char(const char *value_data);
char *int_to_float(const char *value_data);
char *float_to_char(const char *value_data);
char *float_to_int(const char *value_data);
char *float_to_float(const char *value_data);

}  // namespace common
