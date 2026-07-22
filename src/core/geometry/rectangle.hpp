//
// Created by Dean Wilson on 28/6/2025.
//

#pragma once

#include "core/spatial/i-size-2d.hpp"
#include "core/math/vector-2d.hpp"

namespace Core::Geometry {

struct Rectangle {
  float x, y, width, height;

  Rectangle(const float x, const float y, const float width, const float height)
      : x(x), y(y), width(width), height(height) {};

  Rectangle(const Math::Vector2D position, const Core::Spatial::ISize2D& size)
      : x(position.x), y(position.y), width(size.GetWidth()), height(size.GetHeight()) {};
};
}  // namespace Core::Geometry
