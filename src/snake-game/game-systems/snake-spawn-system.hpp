#pragma once

#include "engine/systems/game-systems/game-system.hpp"
#include "snake-game/game-entities/snake-head.hpp"
#include "snake-game/game-entities/snake-segment.hpp"

namespace Core::Entities {
class IEntityManager;
}

namespace Core::Events {
class IEventBus;
}

namespace SnakeGame {
struct SnakeGameSettings;
}

namespace SnakeGame {

struct SnakeSpawnSystemParams {
  const SnakeGameSettings& settings;
  const int screenWidth;
  const int screenHeight;
};

class SnakeSpawnSystem : public Engine::Systems::GameSystem {
 public:
  SnakeSpawnSystem(
      Core::Events::IEventBus& eventBus, Core::Entities::IEntityManager& entityManager,
      SnakeSpawnSystemParams& params
  );
  ~SnakeSpawnSystem();

  virtual void OnRegistration() override;
  void Spawn();
  void Reset();
  void TeardownBody();

 private:
  void CreateSegment(SnakeSegmentParams params);
  void CreateHead();
  const Core::Math::Vector2D GetRandomPosition() const;
  void CreateBody();

  const SnakeGameSettings& settings;
  int screenWidth;
  int screenHeight;
  SnakeHead* head;
};
}  // namespace SnakeGame
