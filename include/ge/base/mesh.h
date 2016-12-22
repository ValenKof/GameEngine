// Created by Valentin Kofman on 20/08/16.
#pragma once
#include "ge/base/point.h"
#include "ge/base/matrix.h"
#include <vector>
#include <array>
#include <fstream>
#include <sstream>

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

    FillNormals();
  }

  void LoadObj(const std::string& path)
  {
    std::ifstream in(path);

    m_points.clear();
    m_polygons.clear();

    std::vector<std::array<int32_t, 3>> obj_polygons;

    std::string line;
    while (std::getline(in, line)) {
      std::stringstream sstr(line);
      std::string token;
      sstr >> token;
      if (token == "#") {
        continue;
      } else if (token == "v") {
        float x, y, z;
        sstr >> x >> y >> z;
        m_points.emplace_back(x, y, z);
      } else if (token == "f") {
        std::array<int32_t, 3> polygon;
        for (size_t i = 0; i < 3; ++i) {
          sstr >> token;
          std::replace(token.begin(), token.end(), '/', ' ');
          std::stringstream indices(token);
          indices >> polygon[i];
        }
        std::swap(polygon[1], polygon[2]);
        obj_polygons.push_back(polygon);
      }
    }

    int32_t sz = static_cast<int32_t>(m_points.size());
    auto normalize = [=](int32_t index) {
      return static_cast<uint16_t>((sz + index) % sz);
    };
    for (const auto& p : obj_polygons) {
      m_polygons.push_back({{ normalize(p[0]), normalize(p[1]), normalize(p[2]) }});
    }

    FillNormals();
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
  {
    auto p = GetPolygon(index);
    auto n = m_normals[index];
    return p[0].ToRadiusVector().DotProduct(n) <= 0 &&
      p[1].ToRadiusVector().DotProduct(n) <= 0 &&
      p[2].ToRadiusVector().DotProduct(n) <= 0;
  }

  size_t PolygonsNumber() const
  { return m_polygons.size(); }

private:
  void FillNormals() {
    auto normal = [this](const auto& polygon) {
      auto p = m_points[polygon[1]] - m_points[polygon[0]];
      auto q = m_points[polygon[2]] - m_points[polygon[0]];
      return q.CrossProduct(p).Normalized();
    };
    m_normals.resize(m_polygons.size());
    std::transform(m_polygons.begin(), m_polygons.end(), m_normals.begin(), normal);
  }

  std::vector<BasicPoint3D<T>> m_points;
  std::vector<std::array<uint16_t, 3>> m_polygons;
  std::vector<BasicVector3D<T>> m_normals;
};

using Mesh = BasicMesh<float>;

}  // namespace ge
