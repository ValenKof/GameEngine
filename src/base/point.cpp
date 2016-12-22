// Created by Valentin Kofman on 30/08/16.
#include "ge/base/point.h"

namespace ge {

template <typename T>
BasicPoint3D<T>::BasicPoint3D()
{}

template <typename T>
BasicPoint3D<T>::BasicPoint3D(T x, T y, T z)
  : x(x)
  , y(y)
  , z(z)
{}

template <typename T>
BasicRow<T> BasicPoint3D<T>::ToRowVector() const
{
  BasicRow<T> result;
  result(0, 0) = x;
  result(0, 1) = y;
  result(0, 2) = z;
  result(0, 3) = static_cast<T>(1);
  return result;
}

template <typename T>
BasicPoint3D<T> BasicPoint3D<T>::FromRowVector(BasicRow<T> row)
{ return {row(0, 0) / row(0, 3), row(0, 1) / row(0, 3), row(0, 2) / row(0, 3)}; }

template <typename T>
BasicVector3D<T> BasicPoint3D<T>::ToRadiusVector() const
{ return {x, y, z}; }

template struct BasicPoint3D<float>;
template struct BasicPoint3D<double>;

}  // namespace ge
