//
// Created by Valentin Kofman on 05/08/16.
//
#pragma once
#include <stdexcept>

#define LIKELY(x)   __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

#define ASSERT(x)                         \
  do {                                    \
    if (UNLIKELY(!(x))) {                 \
      throw std::runtime_error(#x);       \
    }                                     \
  } while (false)                         \

