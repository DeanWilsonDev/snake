#pragma once

#include "../core/entity.h"
#include "snake-segment.hpp"
#include <deque>
#include "Settings/game-settings.h"

namespace Renderer2D::Component {
class IRenderComponent2D;
}

namespace Game {

struct SnakeParams {
  Renderer2D::Component::IRenderComponent2D& renderComponent;
  GameSettings& settings;
};

class Snake final : Core::Entity {
 public:
  ~Snake() override;
  explicit Snake(const SnakeParams& snakeParams);

  Snake* Initialize();
  void Update(float deltaTime) override;
  void Destroy();
  void Move();
  void CheckIfShouldGrow();
  void Teleport() const;

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
  GameSettings& settings;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;

};
}  // namespace Game
