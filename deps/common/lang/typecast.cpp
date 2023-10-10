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
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    },
    { // ints
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    },
    { // floats
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
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

  void *char_to_int(const char *value_data)
  {
    assert(nullptr != value_data);
    void *res = malloc(sizeof(int));
    int tmp = atoi((char *)value_data);
    memcpy(res, &tmp, sizeof(int));
    return res;
  }
}