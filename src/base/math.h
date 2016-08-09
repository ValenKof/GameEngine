#pragma once

namespace ge {

inline double sqr(double x) {
  return x * x;
}

template<typename T, typename ValueType>
struct Scalar {
  friend T operator+(const T& one, const T& other) { return T(one) += other; }
  friend T operator+(const T& one, T&& other) { return T(std::move(other)) += one; }
  friend T operator+(T&& one, const T& other) { return T(std::move(one)) += other; }
  friend T operator+(T&& one, T&& other) { return T(std::move(one)) += other; }

  friend T operator-(const T& one, const T& other) { return T(one) -= other; }
  friend T operator-(T&& one, const T& other) { return T(std::move(one)) -= other; }

  friend T operator*(const T one, const ValueType& other) { return T(one) *= other; }
  friend T operator*(T&& one, const ValueType& other) { return T(std::move(one)) *= other; }
  friend T operator*(const ValueType& one, const T& other) { return T(other) *= one; }
  friend T operator*(const ValueType& one, T&& other) { return T(std::move(other)) *= one; }

  friend T operator/(const T& one, const ValueType& other) { return T(one) /= other; }
  friend T operator/(T&& one, const ValueType& other) { return T(std::move(one)) /= other; }
};

}  // namespace ge
