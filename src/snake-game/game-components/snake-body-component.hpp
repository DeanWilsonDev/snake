#pragma once

#include "engine/components/game-component.hpp"
#include <deque>

namespace SnakeGame {
class SnakeSegment;
}

namespace SnakeGame {
struct SnakeSegmentParams;
}

namespace SnakeGame {
class SnakeHead;
}

namespace SnakeGame {

class SnakeBodyComponent final : public Engine::Components::GameComponent {
 public:
  SnakeBodyComponent();

  virtual void Update(const float) override;

  void Append(SnakeSegment* segment);
  void Clear();
  [[nodiscard]] const std::deque<SnakeSegment*>& GetSegments() const;

 private:
  std::deque<SnakeSegment*> segments;
  int length = {3};
};

}  // namespace SnakeGame
