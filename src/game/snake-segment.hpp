#pragma once

#include "core/math/transform-2d.hpp"

namespace Physics::Components {
class ColliderComponent2D;
}
namespace Game {


struct SnakeSegmentParams {
  int index;
  UserInterface::Math::Transform2D transform;
  Physics::Components::ColliderComponent2D* colliderComponent;
};

class SnakeSegment final {
 public:
  // Properties
  int index = {0};
  UserInterface::Math::Transform2D transform = {UserInterface::Math::Transform2D::Empty()};

  // Constructor
  explicit SnakeSegment(const SnakeSegmentParams& props);
  ~SnakeSegment();

  // Methods
  SnakeSegment* Initialize(int index, const UserInterface::Math::Transform2D& transform);
  void Move(UserInterface::Math::Vector2D newPosition);

  [[nodiscard]] Physics::Components::ColliderComponent2D* GetColliderComponent() const
  {
    return this->colliderComponent;
  }

 private:
  Physics::Components::ColliderComponent2D* colliderComponent{};
};
}  // namespace Game
