//
// Created by Dean Wilson on 28/6/2025.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace Core::Math::Geometry {

struct Rectangle {
  float x, y, width, height;

  Rectangle(float x, float y, float width, float height);
  explicit Rectangle(const Transform2D& transform)
      : x(transform.position.x)
      , y(transform.position.y)
      , width(transform.scale.x)
      , height(transform.scale.y) {};

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
