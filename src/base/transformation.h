#pragma once
#include <base/matrix.h>

namespace ge {

struct Transformation {
  static Matrix<double> Translate(double dx, double dy, double dz)
  { return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {dx, dy, dz, 1}}; }

  static Matrix<double> Scale(double f)
  { return {{f, 0, 0, 0}, {0, f, 0, 0}, {0, 0, f, 0}, {0, 0, 0, 1}}; }
};

}  // namespace ge
