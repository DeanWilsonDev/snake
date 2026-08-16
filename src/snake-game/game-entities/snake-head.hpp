#pragma once

#include "core/spatial/i-transform-2d.hpp"
#include "snake-game/game-components/movement-component.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "engine/input/components/input-component.hpp"

namespace Core::Input {
class ActionRouter;
}

namespace SnakeGame {

struct SnakeHeadParams : SnakeSegmentParams {
  SnakeHeadParams(
      const int index, const Core::Spatial::ITransform2D& transform, const bool active = true
  )
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

 private:
  Engine::Input::Components::InputComponent* inputComponent{nullptr};
  MovementComponent* movementComponent{nullptr};
};

}  // namespace SnakeGame
