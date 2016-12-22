// Created by Valentin Kofman on 05/12/16.
#include "ge/base/png.h"
#include <lodepng/lodepng.h>
#include <iostream>

namespace ge {

void Image::LoadPng(const std::string& path)
{
  std::vector<unsigned char> png;
  auto error = lodepng::load_file(png, path);
  if (!error) {
    error = lodepng::decode(m_data, m_width, m_height, png);
  }
  if (error) {
    std::cerr << "decoder error: " << error
      << " text" << lodepng_error_text(error) << std::endl;
    exit(0);
  } else {
    std::cout << "image loaded " << m_width << 'x' << m_height << std::endl;
  }
}

}  // namespace ge
