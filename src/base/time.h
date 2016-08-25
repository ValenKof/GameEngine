//
// Created by Valentin Kofman on 25/08/16.
//
#pragma once
#include "x86intrin.h"

namespace ge {

inline int64_t Ticks()
{ return __rdtsc(); }

inline int64_t TicksPerSecond()
{
  static constexpr int64_t kTicksPerSeconds = 2'700'000'000;
  return kTicksPerSeconds;
}

}  // namespace ge
