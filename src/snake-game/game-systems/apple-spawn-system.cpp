#include "apple-spawn-system.hpp"
#include <memory>
#include "core/math/vector-2d.hpp"
#include "engine/systems/game-systems/game-system.hpp"
#include "snake-game/game-events/game-started-event.hpp"
#include "snake-game/game-events/apple-collected-event.hpp"
#include "core/utils/get-random-value.hpp"
#include "engine/spatial/transform-2d.hpp"
#include "core/entities/i-entity-manager.hpp"
#include "core/events/i-event-bus.hpp"
#include "snake-game/game-entities/apple.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"

namespace SnakeGame {

AppleSpawnSystem::AppleSpawnSystem(
    Core::Events::IEventBus& eventBus, Core::Entities::IEntityManager& entityManager,
    AppleSpawnSystemParams& params
)
    : Engine::Systems::GameSystem(eventBus, entityManager)
    , screenWidth(params.screenWidth)
    , screenHeight(params.screenHeight)
{
}

void AppleSpawnSystem::OnRegistration()
{
  this->apple = static_cast<Apple*>(
      this->entityManager.AddEntity(
          std::make_unique<Apple>(AppleParams(
              Engine::Spatial::Transform2D{
                  this->GetRandomPosition(), 0, Engine::Spatial::Size2D{1, 1}
              }
          ))
      )

  );

  this->eventBus.Subscribe<GameStartedEvent>([this](const auto&) { this->Spawn(); });
  this->eventBus.Subscribe<AppleCollectedEvent>([this](const auto&) { this->Spawn(); });
}

void AppleSpawnSystem::Spawn() const
{
  this->apple->SetActive(false);
  this->apple->transform->SetPosition(this->GetRandomPosition());
  this->apple->SetActive(true);
}

const Core::Math::Vector2D AppleSpawnSystem::GetRandomPosition() const
{
  return {
      static_cast<float>(Core::Utils::GetRandomValue(0, this->screenWidth)),
      static_cast<float>(Core::Utils::GetRandomValue(0, this->screenHeight))
  };
}

}  // namespace SnakeGame
