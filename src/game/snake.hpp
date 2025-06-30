#pragma once

#include "core/entity.h"
#include <deque>


namespace Physics::Components {
class ColliderComponent2D;
}

namespace Renderer2D::Component {
class IRenderComponent2D;
}

namespace Game {
class Apple;

class SnakeSegment;
struct GameSettings;

struct SnakeParams {
  Renderer2D::Component::IRenderComponent2D& renderComponent;
  Physics::Components::ColliderComponent2D& colliderComponent;
  GameSettings& settings;
};

class Snake final : public Core::Entity {
 public:
  ~Snake() override;
  explicit Snake(const SnakeParams& snakeParams);

  Snake* Initialize();
  void Update(float deltaTime) override;
  void Destroy();
  void Move();
  void CheckIfShouldGrow();
  void Teleport() const;
  Core::Math::Vector2D GetCenter() const;
  void SetGrow(bool value) { this->grow = value; }

  // Getters
  Physics::Components::ColliderComponent2D& GetColliderComponent() const
  {
    return this->colliderComponent;
  }

  // Side Quest: [Snake] fix up the access on public variables. Add getters and setters where necessary
  float size;
  float speed;
  int length;
  Core::Math::Vector2D direction;
  SnakeSegment* head;
  std::deque<SnakeSegment*> body;
  bool grow = false;
  bool debugEnabled = false;

 private:
  Renderer2D::Component::IRenderComponent2D& renderComponent;
  Physics::Components::ColliderComponent2D& colliderComponent;
  GameSettings& settings;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
};
}  // namespace Game
