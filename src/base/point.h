//
// Created by Valentin Kofman on 08/08/16.
//
#pragma once
#include <base/math.h>
#include <base/matrix.h>
#include <iostream>
#include <cmath>

namespace ge {

template <typename BasicVector3D>
struct BasicVector3D;

template <typename T>
struct BasicPoint3D {
  BasicPoint3D();
  BasicPoint3D(T x, T y, T z);
  BasicRow<T> ToRowVector() const;
  static BasicPoint3D FromRowVector(BasicRow<T> row);
  BasicVector3D<T> ToRadiusVector() const;

  T x;
  T y;
  T z;
};

template <typename T>
inline std::ostream& operator<<(std::ostream& ostr, const BasicPoint3D<T>& p)
{ return ostr << '(' << p.x << ',' << p.y << ',' << p.z << ')'; }

using Point3D = BasicPoint3D<float>;

template <typename T>
struct BasicVector3D {
  BasicVector3D() {}
  BasicVector3D(T x, T y, T z) : x(x), y(y), z(z) {}

  T DotProduct(const BasicVector3D& v) const
  { return x * v.x + y * v.y + z * v.z; }

  BasicVector3D CrossProduct(const BasicVector3D& v) const
  { return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x}; }

  T SquaredLength() const
  { return DotProduct(*this); }

  T Length() const
  { return sqrt(SquaredLength()); }

  BasicRow<T> ToRowVector() const
  {
    BasicRow<T> result;
    result(0, 0) = x;
    result(0, 1) = y;
    result(0, 2) = z;
    result(0, 3) = static_cast<T>(0);
    return result;
  }

  static BasicVector3D FromRowVector(BasicRow<T> row)
  { return {row(0, 0), row(0, 1), row(0, 2)}; }

  BasicVector3D operator-() const
  { return {-x, -y, -z}; }

  BasicVector3D Normalized() const
  {
    T length = Length();
    return {x / length, y / length, z / length};
  }

  T x;
  T y;
  T z;
};

template <typename T>
inline std::ostream& operator<<(std::ostream& ostr, const BasicVector3D<T>& v)
{ return ostr << '[' << v.x << ',' << v.y << ',' << v.z << ']'; }

using Vector3D = BasicVector3D<float>;

template <typename T>
inline BasicVector3D<T> operator-(const BasicPoint3D<T>& a, const BasicPoint3D<T>& b)
{ return {a.x - b.x, a.y - b.y, a.z - b.z}; }

template <typename T>
inline BasicPoint3D<T> operator+(const BasicPoint3D<T>& a, const BasicVector3D<T>& b)
{ return {a.x + b.x, a.y + b.y, a.z + b.z}; }

template <typename T>
inline BasicPoint3D<T> operator+(const BasicVector3D<T>& a, const BasicPoint3D<T>& b)
{ return {a.x + b.x, a.y + b.y, a.z + b.z}; }

template <typename T>
inline BasicVector3D<T> operator+(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return {a.x + b.x, a.y + b.y, a.z + b.z}; }

template <typename T>
inline BasicVector3D<T> operator-(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return {a.x - b.x, a.y - b.y, a.z - b.z}; }

template <typename T>
inline BasicVector3D<T> operator*(const BasicVector3D<T>& a, T b)
{ return {a.x * b, a.y * b, a.z * b}; }

template <typename T>
inline BasicVector3D<T> operator*(T a, const BasicVector3D<T>& b)
{ return b * a; }

}  // namespace ge
