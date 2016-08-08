//
// Created by Valentin Kofman on 05/08/16.
//
#pragma once
#include <base/assert.h>
#include <memory>
#include <iostream>

namespace ge {

template<typename T>
class Matrix {
public:
  Matrix(uint32_t rowsNum, uint32_t colsNum) {
    Init(rowsNum, colsNum);
  }

  Matrix() {
    Init(0, 0);
  }

  Matrix(std::initializer_list<std::initializer_list<T>> list) {
    Init(list.size(), list.size() > 0 ? list.size() : 0);
    for (uint32_t row = 0; row < m_rowsNum; ++row) {
      std::initializer_list<T> sublist = *std::next(list.begin(), row);
      ASSERT(sublist.size() == m_colsNum);
      for (uint32_t col = 0; col < m_colsNum; ++col) {
        (*this)(row, col) = *std::next(sublist.begin(), col);
      }
    }
  }

  Matrix(Matrix&& matrix) noexcept {
    (*this) = std::move(matrix);
  }

  Matrix& operator=(Matrix&& matrix) noexcept {
    m_rowsNum = matrix.m_rowsNum;
    matrix.m_rowsNum = 0;
    m_colsNum = matrix.m_colsNum;
    matrix.m_colsNum = 0;
    m_data = std::move(matrix.m_data);
    return *this;
  }

  Matrix(const Matrix& matrix) = delete;

  Matrix& operator=(const Matrix& matrix) = delete;

  Matrix Clone() const {
    Matrix clone(m_rowsNum, m_colsNum);
    for (uint32_t row = 0; row < m_rowsNum; ++row) {
      for (uint32_t col = 0; col < m_colsNum; ++col) {
        clone(row, col) = (*this)(row, col);
      }
    }
    return clone;
  }

  T& operator()(uint32_t row, uint32_t col) {
    ASSERT(0 <= row && row < m_rowsNum);
    ASSERT(0 <= col && col < m_colsNum);
    return m_data[row * m_colsNum + col];
  }

  const T& operator()(uint32_t row, uint32_t col) const {
    ASSERT(0 <= row && row < m_rowsNum);
    ASSERT(0 <= col && col < m_colsNum);
    return m_data[row * m_colsNum + col];
  }

  Matrix& operator+=(const Matrix& other) {
    ASSERT(m_rowsNum == other.m_rowsNum);
    ASSERT(m_colsNum == other.m_colsNum);
    for (uint32_t row = 0; row < m_rowsNum; ++row) {
      for (uint32_t col = 0; col < m_colsNum; ++col) {
        (*this)(row, col) += other(row, col);
      }
    }
    return *this;
  }

  Matrix& operator-=(const Matrix& other) {
    ASSERT(m_rowsNum == other.m_rowsNum);
    ASSERT(m_colsNum == other.m_colsNum);
    for (uint32_t row = 0; row < m_rowsNum; ++row) {
      for (uint32_t col = 0; col < m_colsNum; ++col) {
        (*this)(row, col) -= other(row, col);
      }
    }
    return *this;
  }

  Matrix& operator*=(const T& other) {
    for (uint32_t row = 0; row < m_rowsNum; ++row) {
      for (uint32_t col = 0; col < m_colsNum; ++col) {
        (*this)(row, col) *= other;
      }
    }
    return *this;
  }

  Matrix& operator/=(const T& other) {
    for (uint32_t row = 0; row < m_rowsNum; ++row) {
      for (uint32_t col = 0; col < m_colsNum; ++col) {
        (*this)(row, col) /= other;
      }
    }
    return *this;
  }

  bool Empty() const {
    return m_rowsNum == 0 || m_colsNum == 0;
  }

  uint32_t RowsNum() const {
    return m_rowsNum;
  }

  uint32_t ColsNum() const {
    return m_colsNum;
  }

private:
  void Init(uint32_t rowsNum, uint32_t colsNum) {
    ASSERT((rowsNum == 0) == (colsNum == 0));
    m_rowsNum = rowsNum;
    m_colsNum = colsNum;
    if (!Empty()) {
      m_data = std::make_unique<T[]>(m_rowsNum * m_colsNum);
    } else {
      m_data = nullptr;
    }
  }

  uint32_t m_rowsNum;
  uint32_t m_colsNum;
  std::unique_ptr<T[]> m_data;
};

template<typename T>
Matrix<T> operator+(const Matrix<T>& one, const Matrix<T>& other) {
  Matrix<T> result = one.Clone();
  result += other;
  return result;
}

template<typename T>
Matrix<T> operator-(const Matrix<T>& one, const Matrix<T>& other) {
  Matrix<T> result = one.Clone();
  result -= other;
  return result;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& one, const T& other) {
  Matrix<T> result = one.Clone();
  result *= other;
  return result;
}

template<typename T>
Matrix<T> operator*(const T& one, const Matrix<T>& other) {
  return other * one;
}

template<typename T>
Matrix<T> operator/(const Matrix<T>& one, const T& other) {
  Matrix<T> result = one.Clone();
  result /= other;
  return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& ostr, const Matrix<T>& matrix) {
  for (uint32_t row = 0; row < matrix.RowsNum(); ++row) {
    for (uint32_t col = 0; col < matrix.ColsNum(); ++col) {
      ostr << matrix(row, col) << ' ';
    }
    ostr << '\n';
  }
  return ostr;
}

}  // namespace ge
