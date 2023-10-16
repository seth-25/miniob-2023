//
// Created by seth on 2023/10/9.
//

#include "typecast.h"
#include <cassert>
#include <cstring>

namespace common {

cast_func_ptr type_cast_to[AttrType::BOOLEANS + 1][AttrType::BOOLEANS + 1] = {
    { // undefined
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    },
    { // chars
        nullptr,
        nullptr,
        char_to_int,  // char to int
        nullptr,
        char_to_float,  // char to float
        nullptr,
    },
    { // ints
        nullptr,
        int_to_char,  // int to char
        nullptr,
        nullptr,
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
    },
    { // floats
        nullptr,
        float_to_char,  // float to char
        float_to_int,  // float to int
        nullptr,
        nullptr,
        nullptr,
    },
    { // booleans
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
    std::string res = std::to_string(*(float *) value_data);
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
}