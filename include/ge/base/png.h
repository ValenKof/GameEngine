// Created by Valentin Kofman on 05/12/16.
#pragma once
#include "ge/base/color.h"
#include <cstdint>
#include <vector>
#include <string>

namespace ge {

class Image {
public:
  Image(): m_width(0), m_height(0) {}

  void LoadPng(const std::string& path);

  uint8_t Red(uint32_t row, uint32_t column) const
  { return GetByte(row, column, 0); }

  uint8_t Green(uint32_t row, uint32_t column) const
  { return GetByte(row, column, 1); }

  uint8_t Blue(uint32_t row, uint32_t column) const
  { return GetByte(row, column, 2); }

  uint8_t Alpha(uint32_t row, uint32_t column) const
  { return GetByte(row, column, 3); }

  Color GetPixel(uint32_t row, uint32_t column) const
  { return Color::FromRgb(Red(row, column), Green(row, column), Blue(row, column)); }

  uint32_t Height() const { return m_height; }

  uint32_t Width() const { return m_width; }

private:
  uint8_t GetByte(uint32_t row, uint32_t column, uint32_t index) const
  { return m_data[(row * m_width + column) * 4 + index]; }

  unsigned m_width;
  unsigned m_height;
  std::vector<unsigned char> m_data;
};

}  // namespace ge
