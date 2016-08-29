#pragma once
#include <base/matrix.h>
#include <array>

namespace ge {

struct Textures {
  static BasicMatrix<float, 3, 2> ModelToTextureTransformation(
      const BasicMatrix<float, 3, 3>& model_matrix,
      const BasicMatrix<float, 3, 2>& texture_matrix)
  { return model_matrix.Inversed() * texture_matrix; }

  static std::array<std::array<float, 3>, 2> ModelToTextureTransformation(
      const std::array<std::array<float, 3>, 3>& model_points,
      const std::array<std::array<float, 2>, 3>& texture_points)
  {
    BasicMatrix<float, 3, 3> model;
    model.data = model_points;
    BasicMatrix<float, 3, 2> texture;
    texture.data = texture_points;
    return ModelToTextureTransformation(model, texture).Transposed().data;
  }
};

}  // namespace ge
