//
// Created by Valentin Kofman on 26/08/16.
//
#pragma once
#include <base/matrix.h>
#include <base/point.h>
#include <base/transformation.h>
#include <cmath>

namespace ge {

class Camera {
public:
  static constexpr double kPi = 3.1415;
  static constexpr double kFowAngle = 90 * kPi / 360;
  static constexpr int kWidth = 800;
  static constexpr int kHeight = 600;
  static constexpr double kAspectRatio = 1.0 * kWidth / kHeight;
  static constexpr double kNear = -0.1;
  static constexpr double kFar = -1.0;

  Camera(Point3D location, Vector3D direction, Vector3D up)
    : m_location(location)
    , m_direction(direction.Normalized())
    , m_up(up.Normalized())
  {
    Vector3D i = direction.CrossProduct(up).Normalized();
    Vector3D j = i.CrossProduct(direction).Normalized();
    Vector3D k = (-direction).Normalized();
    Matrix t = BasicIdentity<float>();
    t(0, 0) = i.x; t(0, 1) = i.y; t(0, 2) = i.z;
    t(1, 0) = j.x; t(1, 1) = j.y; t(1, 2) = j.z;
    t(2, 0) = k.x; t(2, 1) = k.y; t(2, 2) = k.z;
    // t.Inversed() == t.Transposed()

    Matrix c = BasicZeroes<float>();
    double fow = 1 / tan(kFowAngle / 2);
    c(0, 0) = fow * kAspectRatio;
    c(1, 1) = fow;
    c(2, 2) = (kFar + kNear) / (kFar - kNear);
    c(2, 3) = -1;
    c(3, 2) = - 2 * kNear * kFar / (kFar - kNear);

    m_world_to_camera =
        Transformation::Translate(Point3D(0, 0, 0) - location) * t.Transposed();
    m_clip = c;
  }

  Point3D Location() const
  { return m_location; }

  Matrix WorldToCamera() const
  { return m_world_to_camera * m_clip; }

  Matrix CameraToProjection() const
  { return m_clip; }

  Camera TranslateLocation(Vector3D v) const
  { return {m_location + v, m_direction, m_up}; }

  Vector3D Direction() const
  { return m_direction; }

  Vector3D Up() const
  { return m_up; }

  Vector3D Right() const
  { return m_direction.CrossProduct(m_up).Normalized(); }

  Vector3D Left() const
  { return -Right(); }

  Camera TurnRight(float angle) const
  { return {m_location, m_direction + (Right() - m_direction) * angle, m_up}; }

  Camera TurnLeft(float angle) const
  { return TurnRight(-angle); }

private:
  Point3D m_location;
  Vector3D m_direction;
  Vector3D m_up;
  Matrix m_world_to_camera;
  Matrix m_clip;
};

}  // namespace ge
