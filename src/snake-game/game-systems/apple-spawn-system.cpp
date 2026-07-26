#include "apple-spawn-system.hpp"
#include "snake-game/game-events/game-started-event.hpp"
#include "snake-game/game-events/apple-collected-event.hpp"

namespace SnakeGame {

void AppleSpawnSystem::OnRegistration()
{
  this->eventBus.Subscribe<GameStartedEvent>([this](const auto&) { this->RespawnApple(); });
  this->eventBus.Subscribe<AppleCollectedEvent>([this](const auto&) { this->RespawnApple(); });
}

void AppleSpawnSystem::RespawnApple() const {}

}  // namespace SnakeGame
