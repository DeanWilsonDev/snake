#pragma once

#include "core/math/vector-2d.hpp"
#include "core/spatial/i-transform-2d.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "engine/input/components/input-component.hpp"

namespace Core::Input {
class ActionRouter;
}

namespace SnakeGame {

struct SnakeHeadParams : SnakeSegmentParams {
  SnakeHeadParams(int index, Core::Spatial::ITransform2D* transform, bool active = true)
      : SnakeSegmentParams(index, transform, active)
  {

  }
};

class SnakeHead final : public SnakeSegment {
 public:
  explicit SnakeHead(const SnakeHeadParams& params);

  void OnRegistration() override;
  virtual void BeginPlay() override;
  virtual void Update(const float deltaTime) override;
  virtual void DebugUpdate() const override;
  void Move() const;
  [[nodiscard]] Core::Math::Vector2D GetDirection() { return this->direction; }
  void SetDirection(Core::Math::Vector2D direction);

 private:
  Core::Math::Vector2D direction = Core::Math::Vector2D::Zero();
  Core::Math::Vector2D pendingDirection = Core::Math::Vector2D::Zero();
  Engine::Input::Components::InputComponent* inputComponent;
};

}  // namespace SnakeGame
