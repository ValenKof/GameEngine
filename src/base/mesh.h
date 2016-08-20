#include <base/point.h>
#include <base/matrix.h>
#include <vector>
#include <array>

namespace ge {

template <typename T>
class BasicMesh {
public:
  void transform(BasicMatrix<T> transformation) {
    auto point_transformation = transformation;
    for (auto& point : m_points) {
      point = BasicPoint3D<T>::FromRowVector(point.ToRowVector() * point_transformation);
    }
    auto normal_transformation = transformation.Inverse().Transpose();
    for (auto& normal : m_normals) {
      normal = BasicVector3D<T>::FromRowVector(normal.ToRowVector() * normal_transformation);
    }
  }

private:
  std::vector<BasicPoint3D<T>> m_points;
  std::vector<std::array<uint16_t, 3>> m_triangles;
  std::vector<BasicVector3D<T>> m_normals;
};

using Mesh = BasicMesh<float>;

}  // namespace ge
