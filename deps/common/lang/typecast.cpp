//
// Created by seth on 2023/10/9.
//

#include "typecast.h"
#include <cassert>
#include <cstring>
#include "common/lang/string.h"

namespace common {

cast_func_ptr type_cast_to[AttrType::BOOLEANS + 1][AttrType::BOOLEANS + 1] = {
    { // undefined
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    },
    { // chars
        nullptr,  // char to undefined
        nullptr,  // char to char
        char_to_int,  // char to int
        nullptr,  // char to date
        nullptr,  // char to text
        nullptr, // char to null
        char_to_float,  // char to float
        nullptr,  // char to boolean
    },
    { // ints
        nullptr,  // int to undefined
        int_to_char,  // int to char
        nullptr,  // int to int
        nullptr,  // int to date
        nullptr,   // int to text
        nullptr,   // int to null
        int_to_float,  // int to float
        nullptr,
    },
    { // dates
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    },
    { // texts
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    },
    { //null
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    },
    { // floats
        nullptr,
        float_to_char,  // float to char
        float_to_int,  // float to int
        nullptr,  // float to date
        nullptr,  // float to text
        nullptr,  // float to null
        float_to_float,   // float to float
        nullptr,  // float to boolean
    },
    { // booleans
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    }
  };

  bool type_cast_check(AttrType x, AttrType y) {
    return type_cast_to[x][y] != nullptr;
  }

  char *char_to_int(const char *value_data)
  {
    assert(nullptr != value_data);
    char *res = static_cast<char *>(malloc(sizeof(int)));
    int num = atoi(value_data);
    memcpy(res, &num, sizeof(int));
    return res;
  }

  char *char_to_float(const char *value_data)
  {
    assert(nullptr != value_data);
    char *res = static_cast<char *>(malloc(sizeof(float)));
    float num = atof(value_data);
    memcpy(res, &num, sizeof(float));
    return res;
  }

  char *int_to_char(const char *value_data)
  {
    assert(nullptr != value_data);
    std::string res = std::to_string(*(int*) value_data);
    return strdup(res.c_str());
  }

  char *int_to_float(const char *value_data)
  {
    assert(nullptr != value_data);
    char *res = static_cast<char *>(malloc(sizeof(float)));
    float num = *(int *)value_data;
    memcpy(res, &num, sizeof(float ));
    return res;
  }

  char *float_to_char(const char *value_data)
  {
    assert(nullptr != value_data);
    std::string res = double_to_str(*(float *) value_data);
    return strdup(res.c_str());
  }

  char *float_to_int(const char *value_data)
  {
    assert(nullptr != value_data);
    char *res = static_cast<char *>(malloc(sizeof(int)));
    int num = *(float*) value_data + 0.5;
    memcpy(res, &num, sizeof(int));
    return res;
  }

  char *float_to_float(const char *value_data)
  {
    assert(nullptr != value_data);
    char *res = static_cast<char *>(malloc(sizeof(float)));
    memcpy(res, (float *)value_data, sizeof(int));
    return res;
  }
}