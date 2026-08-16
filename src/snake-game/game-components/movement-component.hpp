#pragma once

#include "core/spatial/i-transform-2d.hpp"
#include "engine/components/game-component.hpp"
#include "core/math/vector-2d.hpp"
#include "engine/input/components/input-component.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"

namespace SnakeGame {

struct MovementComponentParams {
  float speed = 10.0f;
  float moveTimer = 0.0f;
  float moveInterval = 0.2f;
  float cellSize = 20.0f;
};

class MovementComponent final : public Engine::Components::GameComponent {
 public:
  MovementComponent(
      Engine::Input::Components::InputComponent* inputComponent,
      Engine::Spatial::Components::TransformComponent2D* transform, MovementComponentParams params
  );

  virtual void BeginPlay() override;
  virtual void Update(const float deltaTime) override;
  void DebugUpdate() const override;
  void SetDirection(Core::Math::Vector2D direction);

 private:
  void Step();

  Engine::Input::Components::InputComponent* inputComponent{nullptr};
  Core::Spatial::ITransform2D* transform{nullptr};

  Core::Math::Vector2D direction{};
  Core::Math::Vector2D pendingDirection{};
  float speed = 10.0f;
  float moveTimer = 0.0f;
  float moveInterval = 0.2f;
  float cellSize = 20.0f;
};

}  // namespace SnakeGame
