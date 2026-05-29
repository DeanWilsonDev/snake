#include "physics/collision/rectangle-collider-2d.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake.hpp"
#include "core/logging/log.hpp"
#include <memory>
#include "debug/debug.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "game/game-objects/snake-segment.hpp"
#include "core/entity/game-entity.hpp"
#include "core/color/color.hpp"
#include "core/math/vector-2d.hpp"
#include "renderer-2d/components/render-component-2d.hpp"

#include "core/components/transform-component-2d.hpp"

namespace SnakeGame {

SnakeSegment::SnakeSegment(const SnakeSegmentParams& params)
    : GameEntity(params), index(params.index)
{
  this->transformComponent =
      make_unique<Core::Components::TransformComponent2D>(&params.initialTransform);

  const auto colliderParams = Physics::Collision::Components::ColliderComponentParams{
      .transform = this->transformComponent.get()
  };

  this->colliderComponent =
      std::make_unique<Physics::Collision::Components::ColliderComponent2D>(colliderParams);

  this->renderComponent = make_unique<Renderer2D::Components::RenderComponent2D>(
      *this->transformComponent, Core::Color::Green, this->GetActive()
  );
}

SnakeSegment::~SnakeSegment() {}

void SnakeSegment::Move(const Core::Math::Vector2D newPosition)
{
  this->GetTransformComponent().GetPosition().x = newPosition.x;
  this->GetTransformComponent().GetPosition().y = newPosition.y;
}

void SnakeSegment::Update(float deltaTime)
{
  Engine::Entity::GameEntity::Update(deltaTime);
}
void SnakeSegment::Initialize() {}

void SnakeSegment::DebugUpdate() const
{
  Engine::Entity::GameEntity::DebugUpdate();
  if (index == 0) {
    UMBRA_DEBUG(this->GetActive(), "Snake/Segment-{}/Active", this->index);

    UMBRA_DEBUG(
        this->GetTransformComponent().GetScale().width, "Snake/Segment-{}/Scale/Width", this->index
    );
    UMBRA_DEBUG(
        this->GetTransformComponent().GetScale().height,
        "Snake/Segment-{}/Scale/Height",
        this->index
    );

    UMBRA_DEBUG(
        this->GetTransformComponent().GetPosition().x, "Snake/Segment-{}/Position/X", this->index
    );
    UMBRA_DEBUG(
        this->GetTransformComponent().GetPosition().y, "Snake/Segment-{}/Position/Y", this->index
    );
    UMBRA_DEBUG(
        this->GetColliderComponent().GetCollider().GetWorldRect().x,
        "Snake/Segment-{}/Collision/X",
        this->index
    );
    UMBRA_DEBUG(
        this->GetColliderComponent().GetCollider().GetWorldRect().y,
        "Snake/Segment-{}/Collision/Y",
        this->index
    );
    UMBRA_DEBUG(
        this->GetColliderComponent().GetCollider().GetWorldRect().width,
        "Snake/Segment-{}/Collision/width",
        this->index
    );
    UMBRA_DEBUG(
        this->GetColliderComponent().GetCollider().GetWorldRect().height,
        "Snake/Segment-{}/Collision/height",
        this->index
    );
  }
}
}  // namespace SnakeGame
