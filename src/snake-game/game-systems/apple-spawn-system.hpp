#pragma once

#include "engine/systems/game-systems/game-system.hpp"

namespace SnakeGame {
class AppleSpawnSystem : public Engine::Systems::GameSystem {
 public:
  AppleSpawnSystem();
  ~AppleSpawnSystem();

  virtual void OnRegistration() override;

  void RespawnApple() const;
};
}  // namespace SnakeGame
