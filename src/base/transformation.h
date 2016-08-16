#pragma once
#include <base/matrix.h>

namespace ge {

template <typename T>
struct BasicTransformation {
  static BasicMatrix<T> Translate(T dx, T dy, T dz)
  {
    BasicMatrix<T> result = BasicIdentity<T>();
    result(3, 0) = dx;
    result(3, 1) = dy;
    result(3, 2) = dz;
    return result;
  }

  static BasicMatrix<T> Scale(T f)
  {
    BasicMatrix<T> result = BasicZeroes<T>();
    result(0, 0) = f;
    result(1, 1) = f;
    result(2, 2) = f;
    result(3, 3) = static_cast<T>(1);
    return result;
  }
};

using Transformation = BasicTransformation<float>;

}  // namespace ge
