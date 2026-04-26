#pragma once

#include "core/math/vector-2d.hpp"

namespace SnakeGame {
class AppleSpawner {
 public:
  AppleSpawner();
  ~AppleSpawner();

  [[nodiscard]] Core::Math::Vector2D RespawnApple(
      const int screenWidth, const int screenHeight, const int boxSize
  ) const;
};
}  // namespace SnakeGame
