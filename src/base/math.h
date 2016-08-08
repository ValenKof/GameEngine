#pragma once

namespace ge {

inline double sqr(double x) {
  return x * x;
}

template<typename T, typename ValueType>
struct Scalar {
  friend T operator+(T one, const T& other) {
    one += other;
    return one;
  }

  friend T operator-(T one, const T& other) {
    one -= other;
    return one;
  }

  friend T operator*(T one, const ValueType& other) {
    one *= other;
    return one;
  }

  friend T operator*(const ValueType& one, T other) {
    other *= one;
    return other;
  }

  friend T operator/(T one, const ValueType& other) {
    one /= other;
    return one;
  }
};

}  // namespace ge
