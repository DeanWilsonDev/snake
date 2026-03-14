//
// Created by Dean Wilson 14th March 2026
//

#include "core/color/color-rgba.hpp"

namespace Core {
namespace Color {
inline constexpr ColorRGBA Black = ColorRGBA({0, 0, 0, 255});
inline constexpr ColorRGBA White = {255, 255, 255, 255};
inline constexpr ColorRGBA Red = {255, 0, 0, 255};
inline constexpr ColorRGBA Green = {0, 255, 0, 255};
inline constexpr ColorRGBA Blue = {0, 0, 255, 255};
inline constexpr ColorRGBA Yellow = {255, 255, 0, 255};
inline constexpr ColorRGBA Cyan = {0, 255, 255, 255};
inline constexpr ColorRGBA Magenta = {255, 0, 255, 255};
}  // namespace Color
}  // namespace Core
