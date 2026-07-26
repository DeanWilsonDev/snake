#pragma once

#include "core/events/i-event-bus.hpp"
#include "core/math/vector-2d.hpp"
#include "engine/systems/game-systems/game-system.hpp"
#include "snake-game/settings/snake-game-settings.hpp"
#include "snake-game/game-entities/snake-head.hpp"
#include "snake-game/game-entities/snake-segment.hpp"

namespace SnakeGame {

struct SnakeSpawnSystemParams {
  Core::Events::IEventBus& eventBus;
  // Core::Entities::IEntityManager& entityManager;
  // const SnakeGameSettings& settings;
  int screenWidth;
  int screenHeight;
};

class SnakeSpawnSystem : public Engine::Systems::GameSystem {
 public:
  SnakeSpawnSystem(SnakeSpawnSystemParams params);
  ~SnakeSpawnSystem();

  [[nodiscard]] Core::Math::Vector2D RespawnSnake() const;

 private:
  Core::Events::IEventBus& eventBus;
  SnakeHead* head;
  std::vector<SnakeSegment*> segments;
};
}  // namespace SnakeGame
