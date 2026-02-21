//
// Created by Dean Wilson on 28/6/2025.
//

#pragma once

#include "core/math/size-2d.hpp"
#include "core/math/vector-2d.hpp"

namespace Core::Geometry {

struct Rectangle {
  float x, y, width, height;

  Rectangle(const float x, const float y, const float width, const float height)
      : x(x), y(y), width(width), height(height) {};

  Rectangle(const Core::Math::Vector2D position, const Core::Math::Size2D size)
      : x(position.x), y(position.y), width(size.width), height(size.height) {};

};
}  // namespace Core::Geometry
