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

class Snake final : public UserInterface::Entity {
 public:
  ~Snake() override;
  explicit Snake(const SnakeParams& snakeParams);

  Snake* Initialize();
  void Update(float deltaTime) override;
  void Destroy();
  void Move();
  void CheckIfShouldGrow();
  void Teleport() const;
  [[nodiscard]] UserInterface::Math::Vector2D GetCenter() const;
  void SetGrow(bool value) { this->grow = value; }

  // Getters
  [[nodiscard]] Physics::Components::ColliderComponent2D& GetColliderComponent() const
  {
    return this->colliderComponent;
  }

  SnakeSegment* head{};
  std::deque<SnakeSegment*> body;

 private:
  Renderer2D::Component::IRenderComponent2D& renderComponent;
  Physics::Components::ColliderComponent2D& colliderComponent;
  GameSettings& settings;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
  float size = {0};
  float speed = {10};
  int length = {3};
  UserInterface::Math::Vector2D direction{};
  bool grow = false;
  bool debugEnabled = false;
};
}  // namespace Game
