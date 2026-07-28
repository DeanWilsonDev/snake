#include "snake-spawn-system.hpp"
#include "engine/systems/game-systems/game-system.hpp"
#include "snake-game/game-components/snake-body-component.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake-game/game-events/game-started-event.hpp"
#include "core/utils/get-random-value.hpp"
#include "core/entities/i-entity-manager.hpp"
#include "core/events/i-event-bus.hpp"
#include "snake-game/game-entities/snake.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"
#include "snake-game/game-entities/snake-head.hpp"
#include "snake-game/settings/snake-game-settings.hpp"

namespace SnakeGame {

SnakeSpawnSystem::SnakeSpawnSystem(
    Core::Events::IEventBus& eventBus, Core::Entities::IEntityManager& entityManager,
    SnakeSpawnSystemParams& params
)
    : Engine::Systems::GameSystem(eventBus, entityManager)
    , settings(params.settings)
    , screenWidth(params.screenWidth)
    , screenHeight(params.screenHeight)
{
}

void SnakeSpawnSystem::OnRegistration()
{
  this->GetEventBus().Subscribe<GameStartedEvent>([this](const auto&) { this->Spawn(); });
}

void SnakeSpawnSystem::Spawn()
{
  if (!this->head) {
    this->CreateHead();
    this->CreateBody();
  }
  else {
    this->Reset();
  }
}

void SnakeSpawnSystem::CreateHead()
{
  auto headParams =
      SnakeHeadParams{0, Engine::Spatial::Transform2D(GetRandomPosition(), 0.0f, {1.0f, 1.0f})};
  auto headEntity = std::make_unique<SnakeHead>(headParams);
  this->head = static_cast<SnakeHead*>(this->entityManager.AddEntity(std::move(headEntity)));
}

const Core::Math::Vector2D SnakeSpawnSystem::GetRandomPosition() const
{
  return {
      static_cast<float>(Core::Utils::GetRandomValue(0, this->screenWidth)),
      static_cast<float>(Core::Utils::GetRandomValue(0, this->screenHeight))
  };
}

void SnakeSpawnSystem::CreateBody()
{
  auto headTransform = this->head->transform;
  for (int i = 0; i < this->settings.defaultSnakeLength; i++) {
    auto nextSegmentTransform = Engine::Spatial::Transform2D(
        Core::Math::Vector2D(
            std::round(
                (headTransform->GetPosition().x -
                 headTransform->GetScale().GetWidth() * static_cast<float>(i)) *
                headTransform->GetScale().GetWidth()
            ),
            std::round(
                (headTransform->GetPosition().y / headTransform->GetScale().GetHeight()) *
                headTransform->GetScale().GetHeight()
            )
        ),
        headTransform->GetRotation(),
        headTransform->GetScale()
    );

    auto params = SnakeSegmentParams{i, nextSegmentTransform};
    this->CreateSegment(params);
  }
}

void SnakeSpawnSystem::CreateSegment(SnakeSegmentParams params)
{
  auto segment = std::make_unique<SnakeSegment>(params);
  auto bodyPart = this->entityManager.AddEntity(std::move(segment));
  this->head->GetComponent<SnakeBodyComponent>()->AddBodyPart(static_cast<SnakeSegment*>(bodyPart));
}

void SnakeSpawnSystem::TeardownBody()
{
  auto* body = this->head->GetComponent<SnakeBodyComponent>();

  for (SnakeSegment* segment : body->GetSegments()) {
    this->entityManager.RemoveEntity(segment);
  }

  body->Clear();
}

void SnakeSpawnSystem::Reset()
{
  this->TeardownBody();

  this->entityManager.RemoveEntity(this->head);
  this->head = nullptr;

  this->CreateHead();
  this->CreateBody();
}

}  // namespace SnakeGame
