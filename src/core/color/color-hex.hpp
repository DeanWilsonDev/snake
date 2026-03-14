//
// Created by Dean Wilson 14th March 2026
//

#pragma once
#include <cstdint>

namespace Core {

namespace Color {

struct ColorRGBA;

struct ColorHex {
  uint32_t value;  // 0xRRGGBBAA

  constexpr ColorHex(uint32_t value) : value(value) {};

  static ColorHex From(const ColorRGBA& color);

  ColorHex ToHex() { return *this; };
  ColorRGBA ToRGBA();
};

}  // namespace Color
}  // namespace Core
