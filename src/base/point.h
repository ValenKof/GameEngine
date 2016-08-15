//
// Created by Valentin Kofman on 08/08/16.
//
#pragma once
#include <base/math.h>
#include <base/matrix.h>
#include <iostream>
#include <cmath>

namespace ge {

struct Point3D {
  Point3D() {}
  Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

  Matrix<double> ToRowVector() const
  { return {{x, y, z, 1}}; }

  double x;
  double y;
  double z;
};

inline std::ostream& operator<<(std::ostream& ostr, const Point3D& p)
{ return ostr << '(' << p.x << ',' << p.y << ',' << p.z << ')'; }

struct Vector3D {
  Vector3D() {}
  Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

  double DotProduct(const Vector3D& v) const
  { return x * v.x + y * v.y + z * v.z; }

  double SquaredLength() const
  { return DotProduct(*this); }

  double Length() const
  { return sqrt(SquaredLength()); }

  Matrix<double> ToRowVector() const
  { return {{x, y, z, 0}}; }

  double x;
  double y;
  double z;
};

inline std::ostream& operator<<(std::ostream& ostr, const Vector3D& v)
{ return ostr << '[' << v.x << ',' << v.y << ',' << v.z << ']'; }

inline Vector3D operator-(const Point3D& a, const Point3D& b)
{ return {a.x - b.x, a.y - b.y, a.z - b.z}; }

inline Point3D operator+(const Point3D& a, const Vector3D& b)
{ return {a.x + b.x, a.y + b.y, a.z + b.z}; }

inline Point3D operator+(const Vector3D& a, const Point3D& b)
{ return {a.x + b.x, a.y + b.y, a.z + b.z}; }

inline Vector3D operator+(const Vector3D& a, const Vector3D& b)
{ return {a.x + b.x, a.y + b.y, a.z + b.z}; }

inline Vector3D operator-(const Vector3D& a, const Vector3D& b)
{ return {a.x - b.x, a.y - b.y, a.z - b.z}; }

}  // namespace ge
