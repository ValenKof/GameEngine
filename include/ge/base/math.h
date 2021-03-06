// Created by Valentin Kofman on 08/08/16.
#pragma once

namespace ge {

inline double sqr(double x) {
  return x * x;
}

template <typename T>
inline T abs(T value) {
  return value < T{0} ? -value : +value;
}

}  // namespace ge
