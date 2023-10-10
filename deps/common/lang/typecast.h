//
// Created by seth on 2023/10/9.
//

#pragma once

#include "src/observer/sql/parser/value.h"
namespace common {

typedef void *(*cast_func_ptr)(const char *);  // void* (*) (const char*) 的函数指针

extern cast_func_ptr type_cast_to[AttrType::BOOLEANS + 1][AttrType::BOOLEANS + 1];

/**
 *
 * @param x field_type
 * @param y value_type
 * @return
 */
bool type_cast_check(AttrType x, AttrType y);

void *char_to_int(const char *value_data);

}  // namespace common
