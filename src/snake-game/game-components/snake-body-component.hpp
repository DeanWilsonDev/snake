#pragma once

#include "core/components/i-component.hpp"
#include "core/entities/i-entity.hpp"
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

class SnakeBodyComponent : Core::Components::IComponent {
 public:
  SnakeBodyComponent();

  void AddBodyPart(SnakeSegment* segment);
  void Clear();
  [[nodiscard]] const std::deque<SnakeSegment*>& GetSegments() const;

 private:
  std::deque<SnakeSegment*> segments;
  int length = {3};
};

}  // namespace SnakeGame
