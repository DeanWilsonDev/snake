#include "snake-growth-system.hpp"
#include "engine/spatial/transform-2d.hpp"
#include "engine/systems/game-systems/game-system.hpp"
#include "snake-game/game-components/snake-body-component.hpp"
#include "snake-game/game-events/apple-collected-event.hpp"
#include "core/events/i-event-bus.hpp"

namespace SnakeGame {

SnakeGrowSystem::SnakeGrowSystem(SnakeGrowSystemParams& params)
    : Engine::Systems::GameSystem(params.eventBus)
    , entityManager(params.entityManager)
    , settings(params.settings)
{
}

void SnakeGrowSystem::OnRegistration()
{
  this->eventBus.Subscribe<AppleCollectedEvent>([this](const auto&) { this->Grow(); });
}

void SnakeGrowSystem::Grow()
{
  auto* body = this->head->GetComponent<SnakeBodyComponent>();
  SnakeSegment* tail = body->GetSegments().empty() ? this->head : body->GetSegments().back();

  Engine::Spatial::Transform2D newSegmentTransform {
    tail->transform->GetPosition()

  }

}

}  // namespace SnakeGame
