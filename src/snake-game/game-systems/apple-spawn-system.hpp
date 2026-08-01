#pragma once

#include "core/math/vector-2d.hpp"
#include "engine/systems/game-systems/game-system.hpp"
#include "snake-game/settings/snake-game-settings.hpp"

namespace Core::Events {
class IEventBus;
}

namespace Core::Entities {
class IEntityManager;
}

namespace SnakeGame {
class Apple;
}

namespace SnakeGame {
struct AppleSpawnSystemParams {
  const SnakeGameSettings& settings;
  int screenWidth;
  int screenHeight;
};

class AppleSpawnSystem : public Engine::Systems::GameSystem {
 public:
  explicit AppleSpawnSystem(
      Core::Events::IEventBus& eventBus, Core::Entities::IEntityManager& entityManager,
      AppleSpawnSystemParams& params
  );
  ~AppleSpawnSystem() = default;

  virtual void OnRegistration() override;
  void Spawn() const;

 private:
  const Core::Math::Vector2D GetRandomPosition() const;
  Apple* apple;

  const SnakeGameSettings& settings;
  int screenWidth;
  int screenHeight;
};
}  // namespace SnakeGame
