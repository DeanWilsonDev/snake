
//
// Created by Dean Wilson 14th March 2026
//

#pragma once

namespace Core {

namespace Color {

struct ColorHex;

struct ColorRGBA {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;

  constexpr ColorRGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
      : red(red), green(green), blue(blue), alpha(alpha) {};

  static ColorRGBA From(const ColorHex& hex);
  ColorHex ToHex();
  ColorRGBA ToRGBA() { return *this; };

};  // namespace Color

}  // namespace Color
}  // namespace Core
