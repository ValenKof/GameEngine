// Created by Valentin Kofman on 05/08/16.
#pragma once
#include <cstdint>
#include <cstdlib>

namespace ge {

struct Color {
public:
  static constexpr Color BLACK()   { return FromRgb(0x00, 0x00, 0x00); }
  static constexpr Color BLUE()    { return FromRgb(0x00, 0x00, 0xFF); }
  static constexpr Color GREEN()   { return FromRgb(0x00, 0xFF, 0x00); }
  static constexpr Color CYAN()    { return FromRgb(0x00, 0xFF, 0xFF); }
  static constexpr Color RED()     { return FromRgb(0xFF, 0x00, 0x00); }
  static constexpr Color MAGENTA() { return FromRgb(0xFF, 0x00, 0xFF); }
  static constexpr Color YELLOW()  { return FromRgb(0xFF, 0xFF, 0x00); }
  static constexpr Color WHITE()   { return FromRgb(0xFF, 0xFF, 0xFF); }

  static constexpr Color FromRgb(uint8_t r, uint8_t g, uint8_t b) {
    return FromRgb((uint32_t{r} << 16) | (uint32_t{g} << 8) | (uint32_t{b} << 0));
  }

  static constexpr Color FromRgb(uint32_t rgb) {
    return Color{rgb};
  }

  static Color Random() {
    return FromRgb(rand() & 0xFF, rand() & 0xFF, rand() & 0xFF);
  }

  constexpr uint32_t Rgb() const { return m_rgb; }
  constexpr uint8_t R() const { return static_cast<uint8_t>((m_rgb >> 16) & 0xFF); }
  constexpr uint8_t G() const { return static_cast<uint8_t>((m_rgb >>  8) & 0xFF); }
  constexpr uint8_t B() const { return static_cast<uint8_t>((m_rgb >>  0) & 0xFF); }

private:
  explicit constexpr Color(uint32_t rgb) : m_rgb(rgb) {
  }

  uint32_t m_rgb;
};

}  // namespace ge
