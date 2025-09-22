//
// Created by Dean Wilson on 28/6/2025.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "core/math/transform-2d.hpp"
namespace Core::Math::Geometry {

struct Rectangle {
  float x, y, width, height;

  Rectangle(const float x, const float y, const float width, const float height)
      : x(x), y(y), width(width), height(height) {};

  Rectangle(const Vector2D position, const Size2D size)
      : x(position.x), y(position.y), width(size.width), height(size.height) {};

  explicit Rectangle(ITransform2D& transform)
      : x(transform.GetPosition().x)
      , y(transform.GetPosition().y)
      , width(transform.GetScale().width)
      , height(transform.GetScale().height) {};

  [[nodiscard]] bool Intersects(const Rectangle& other) const
  {
    return !(
        x + width <= other.x || x >= other.x + other.width || y + height <= other.y ||
        y >= other.y + other.height
    );
  }
};
}  // namespace Core::Math::Geometry

#endif  // RECTANGLE_H
