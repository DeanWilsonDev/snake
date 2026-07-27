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

struct SnakeGrowSystemParams {
  Core::Events::IEventBus& eventBus;
  Core::Entities::IEntityManager& entityManager;
  const SnakeGameSettings& settings;
};

class SnakeGrowSystem : public Engine::Systems::GameSystem {
 public:
  SnakeGrowSystem(SnakeGrowSystemParams& params);
  ~SnakeGrowSystem();

  virtual void OnRegistration() override;
  void Grow();

 private:
  Core::Entities::IEntityManager& entityManager;
  const SnakeGameSettings& settings;
  SnakeHead* head;
};
}  // namespace SnakeGame
