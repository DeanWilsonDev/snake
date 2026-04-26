#include "snake-game/game-systems/apple-spawner.hpp"
#include "core/math/vector-2d.hpp"
#include "core/random/get-random-value.hpp"

namespace SnakeGame {

Core::Math::Vector2D AppleSpawner::RespawnApple(
    const int screenWidth, const int screenHeight, const int boxSize
) const
{
  const auto maxWidth = static_cast<int>(screenWidth / boxSize - 1.f);
  const auto maxHeight = static_cast<int>(screenHeight / boxSize - 1.f);

  const auto posX = static_cast<float>(Core::GetRandomValue(0, maxWidth)) * boxSize +
                    (boxSize - boxSize / 2.0f) / 2.0f;

  const auto posY = static_cast<float>(Core::GetRandomValue(0, maxHeight)) * boxSize +
                    (boxSize - boxSize / 2.0f) / 2.0f;

  return {posX, posY};
}

}  // namespace SnakeGame
