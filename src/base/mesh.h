#pragma once
#include <base/point.h>
#include <base/matrix.h>
#include <vector>
#include <array>
#include <fstream>

namespace ge {

template <typename T>
class BasicMesh {
public:
  void LoadTxt(const std::string& path)
  {
    std::ifstream in(path);

    size_t points_number;
    in >> points_number;

    size_t polygons_number;
    in >> polygons_number;

    m_points.resize(points_number);
    for (auto& point : m_points) {
      in >> point.x >> point.y >> point.z;
    }

    m_polygons.resize(polygons_number);
    for (auto& polygon : m_polygons) {
      in >> polygon[0] >> polygon[1] >> polygon[2];
    }

    m_normals.resize(0);
    for (const auto& polygon : m_polygons) {
      auto p = m_points[polygon[1]] - m_points[polygon[0]];
      auto q = m_points[polygon[2]] - m_points[polygon[0]];
      m_normals.push_back(q.CrossProduct(p));
    }
  }

  void Transform(BasicMatrix<T> transformation)
  {
    auto point_transformation = transformation;
    for (auto& point : m_points) {
      point = BasicPoint3D<T>::FromRowVector(point.ToRowVector() * point_transformation);
    }
    auto normal_transformation = transformation.Inversed().Transposed();
    for (auto& normal : m_normals) {
      normal = BasicVector3D<T>::FromRowVector(normal.ToRowVector() * normal_transformation);
    }
  }

  BasicMesh Transformed(BasicMatrix<T> transformation) const
  {
    BasicMesh<T> result(*this);
    result.Transform(transformation);
    return result;
  }

  std::array<BasicPoint3D<T>, 3> GetPolygon(size_t index) const
  {
    const auto& polygon = m_polygons[index];
    return {{m_points[polygon[0]], m_points[polygon[1]], m_points[polygon[2]]}};
  }

  bool IsVisible(size_t index) const
  { return m_normals[index].z > 0; }

  size_t PolygonsNumber() const
  { return m_polygons.size(); }

private:
  std::vector<BasicPoint3D<T>> m_points;
  std::vector<std::array<uint16_t, 3>> m_polygons;
  std::vector<BasicVector3D<T>> m_normals;
};

using Mesh = BasicMesh<float>;

}  // namespace ge
