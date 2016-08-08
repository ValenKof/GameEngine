//
// Created by Valentin Kofman on 08/08/16.
//
#pragma once
#include <base/math.h>
#include <iostream>
#include <cmath>

namespace ge {

struct Point3D : private Scalar<Point3D, double> {
  Point3D() : x(0), y(0), z(0) {}
  Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

  double distance(const Point3D& point) const {
    return std::sqrt(sqr(x - point.x) + sqr(y - point.y) + sqr(z - point.z));
  }

  Point3D& operator+=(const Point3D& point) noexcept {
    x += point.x;
    y += point.y;
    z += point.z;
    return *this;
  }

  Point3D& operator-=(const Point3D& point) noexcept {
    x -= point.x;
    y -= point.y;
    z -= point.z;
    return *this;
  }

  Point3D& operator*=(double d) noexcept {
    x *= d;
    y *= d;
    z *= d;
    return *this;
  }

  Point3D& operator/=(double d) {
    x /= d;
    y /= d;
    z /= d;
    return *this;
  }

  double x;
  double y;
  double z;
};

std::ostream& operator<<(std::ostream& ostr, const Point3D& point) {
  return ostr << '(' << point.x << ',' << point.y << ',' << point.z << ')';
}

}  // namespace ge
