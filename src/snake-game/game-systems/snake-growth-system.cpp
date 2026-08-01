#include "snake-growth-system.hpp"
#include "engine/spatial/transform-2d.hpp"
#include "engine/systems/game-systems/game-system.hpp"
#include "snake-game/game-components/snake-body-component.hpp"
#include "snake-game/game-events/apple-collected-event.hpp"
#include "core/events/i-event-bus.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"

namespace SnakeGame {

SnakeGrowSystem::SnakeGrowSystem(
    Core::Events::IEventBus& eventBus, Core::Entities::IEntityManager& entityManager,
    SnakeGrowSystemParams& params
)
    : Engine::Systems::GameSystem(eventBus, entityManager), settings(params.settings)
{
}

void SnakeGrowSystem::OnRegistration()
{
  this->GetEventBus().Subscribe<AppleCollectedEvent>([this](const auto&) { this->Grow(); });
}

void SnakeGrowSystem::Grow()
{
  auto* body = this->head->GetComponent<SnakeBodyComponent>();
  SnakeSegment* tail = body->GetSegments().empty() ? this->head : body->GetSegments().back();

  Engine::Spatial::Transform2D newSegmentTransform{
      tail->transform->GetPosition(), tail->transform->GetRotation(), tail->transform->GetScale()
  };

  const int newIndex = static_cast<int>(body->GetSegments().size()) + 1;

  auto* rawSegment = static_cast<SnakeSegment*>(this->AddEntity(
      std::make_unique<SnakeSegment>(SnakeSegmentParams{newIndex, newSegmentTransform})
  ));

  body->Append(rawSegment);
}

}  // namespace SnakeGame
