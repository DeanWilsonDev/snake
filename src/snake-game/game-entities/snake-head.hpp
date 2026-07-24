#pragma once

#include "core/math/vector-2d.hpp"
#include "core/spatial/i-transform-2d.hpp"
#include "snake-game/game-entities/snake-segment.hpp"

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

  Core::Math::Vector2D direction = Core::Math::Vector2D::Zero();
};

}  // namespace SnakeGame
