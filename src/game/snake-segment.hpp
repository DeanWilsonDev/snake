#pragma once

#include "../core/math/transform-2d.hpp"

namespace Game {

class SnakeSegment final {
 public:

  // Properties
  int index = {0};
  Core::Math::Transform2D transform = {Core::Math::Transform2D::Empty()};

  // Constructor
  SnakeSegment(int index, const Core::Math::Transform2D& transform);

  // Methods
  SnakeSegment* Initialize(int index, const Core::Math::Transform2D& transform);
  void Move(Core::Math::Vector2D newPosition);
  Core::Math::Vector2D GetBounds() const { return bounds; }

private:
  Core::Math::Vector2D bounds;
};
}  // namespace Game
