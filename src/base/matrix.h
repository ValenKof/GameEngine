//
// Created by Valentin Kofman on 05/08/16.
//
#pragma once
#include <base/assert.h>
#include <base/math.h>
#include <array>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

namespace ge {

#define FOR_EACH_CELL(cmd)             \
  for (uint32_t r = 0; r < R; ++r) {   \
    for (uint32_t c = 0; c < C; ++c) { \
      cmd;                             \
    }                                  \
  }                                    \


template <typename T, uint32_t R, uint32_t C>
struct BasicMatrix;

template <typename T, uint32_t N>
BasicMatrix<T, N, N> BasicIdentity();

template <typename T, uint32_t R = 4, uint32_t C = 4>
struct BasicMatrix {
  BasicMatrix() {}

  void Fill(T value)
  { FOR_EACH_CELL(data[r][c] = value); }

  void Clear()
  { Fill(static_cast<T>(0)); }

  T& operator()(uint32_t r, uint32_t c)
  {
    ASSERT(0 <= r && r < R);
    ASSERT(0 <= c && c < C);
    return data[r][c];
  }

  const T operator()(uint32_t r, uint32_t c) const
  {
    ASSERT(0 <= r && r < R);
    ASSERT(0 <= c && c < C);
    return data[r][c];
  }

  const BasicMatrix<T, C, R> Transposed() const
  {
    BasicMatrix<T, C, R> result;
    FOR_EACH_CELL(result(c, r) = (*this)(r, c));
    return result;
  }

  const BasicMatrix<T, R, C> Inversed() const
  {
    ASSERT(R == C);
    BasicMatrix<T, R, C> self = *this;
    BasicMatrix<T, R, C> result = BasicIdentity<T, R>();
    for (uint32_t i = 0; i < R; ++i) {
      uint32_t best_row = i;
      for (uint32_t j = i + 1; j < R; ++j) {
        if (ge::abs<T>(self(j, i)) > ge::abs<T>(self(best_row, i))) {
          best_row = j;
        }
      }
      T divisor = self(best_row, i);
      for (uint32_t j = 0; j < C; ++j) {
        std::swap(self(i, j), self(best_row, j));
        std::swap(result(i, j), result(best_row, j));
        self(i, j) /= divisor;
        result(i, j) /= divisor;
      }
      for (uint32_t other = 0; other < R; ++other) {
        if (other != i) {
          T multiplier = self(other, i);
          for (uint32_t j = 0; j < C; ++j) {
            self(other, j) -= multiplier * self(i, j);
            result(other, j) -= multiplier * result(i, j);
          }
        }
      }
    }
    return result;
  }

  std::array<std::array<T, C>, R> data;
};

using Matrix = BasicMatrix<float>;

template <typename T>
using BasicRow = BasicMatrix<T, 1, 4>;

using Row = BasicRow<float>;

template <typename T>
using BasicColumn = BasicMatrix<T, 4, 1>;

using Column = BasicColumn<float>;

template <typename T, uint32_t N = 4>
BasicMatrix<T, N, N> BasicIdentity()
{
  BasicMatrix<T, N, N> result;
  result.Clear();
  for (uint32_t i = 0; i < N; ++i) {
    result(i, i) = 1;
  }
  return result;
}

template <typename T, uint32_t N = 4>
BasicMatrix<T, N, N> BasicZeroes()
{
  BasicMatrix<T, N, N> result;
  result.Clear();
  return result;
}

template <typename T, uint32_t R, uint32_t C>
const BasicMatrix<T, R, C> operator+(
    const BasicMatrix<T, R, C>& lhs,
    const BasicMatrix<T, R, C>& rhs)
{
  BasicMatrix<T, R, C> result;
  FOR_EACH_CELL(result(r, c) = lhs(r, c) + rhs(r, c));
  return result;
}

template <typename T, uint32_t R, uint32_t C>
const BasicMatrix<T, R, C> operator-(
    const BasicMatrix<T, R, C>& lhs,
    const BasicMatrix<T, R, C>& rhs)
{
  BasicMatrix<T, R, C> result;
  FOR_EACH_CELL(result(r, c) = lhs(r, c) - rhs(r, c));
  return result;
}

template <typename T, uint32_t R, uint32_t N, uint32_t C>
const BasicMatrix<T, R, C> operator*(
    const BasicMatrix<T, R, N>& lhs,
    const BasicMatrix<T, N, C>& rhs)
{
  BasicMatrix<T, R, C> result;
  FOR_EACH_CELL(
      T sum = 0;
      for (uint32_t i = 0; i < N; ++i) {
        sum += lhs(r, i) * rhs(i, c);
      }
      result(r, c) = sum
  );
  return result;
}

template <typename T, uint32_t R, uint32_t C>
std::ostream& operator<<(std::ostream& ostr, const BasicMatrix<T, R, C>& matrix)
{
  for (uint32_t r = 0; r < R; ++r) {
    ostr << '|';
    for (uint32_t c = 0; c < C; ++c) {
      ostr << matrix(r, c) << ' ';
    }
    ostr << '\n';
  }
  return ostr;
}

#undef FOR_EACH_CELL

}  // namespace ge
