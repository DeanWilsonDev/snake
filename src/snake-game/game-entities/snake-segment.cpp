#include "physics/collision/rectangle-collider-2d.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake.hpp"
#include <memory>
#include "debug/debug.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/entities/i-entity.hpp"
#include "core/color/color.hpp"
#include "core/math/vector-2d.hpp"
#include "renderer-2d/components/render-component-2d.hpp"

#include "engine/spatial/components/transform-component-2d.hpp"

namespace SnakeGame {

SnakeSegment::SnakeSegment(const SnakeSegmentParams& params) : Entity(params), index(params.index)
{
  this->transformComponent =
      make_unique<Engine::Spatial::Components::TransformComponent2D>(&params.initialTransform);
}

SnakeSegment::~SnakeSegment() {}

void SnakeSegment::OnRegistration()
{
  const auto colliderParams = Physics::Collision::Components::ColliderComponentParams{
      .transform = this->transformComponent.get()
  };
  this->AddComponent<Physics::Collision::Components::ColliderComponent2D>(colliderParams);
  this->AddComponent<Renderer2D::Components::RenderComponent2D>(
      *this->transformComponent, Core::Color::Green, this->GetActive()
  );
}

void SnakeSegment::Move(const Core::Math::Vector2D newPosition)
{
  this->GetTransformComponent().GetPosition().x = newPosition.x;
  this->GetTransformComponent().GetPosition().y = newPosition.y;
}

void SnakeSegment::DebugUpdate() const
{
  if (index == 0) {
    UMBRA_DEBUG(this->GetActive(), "Snake/Segment-{}/Active", this->index);

    UMBRA_DEBUG(
        this->GetTransformComponent().GetScale().GetWidth(), "Snake/Segment-{}/Scale/Width", this->index
    );
    UMBRA_DEBUG(
        this->GetTransformComponent().GetScale().GetHeight(),
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

[[nodiscard]] Core::Rendering::Components::IRenderComponent2D&
SnakeSegment::GetRendererComponent2D()
{
  return *this->GetComponent<Core::Rendering::Components::IRenderComponent2D>();
}

[[nodiscard]] Physics::Collision::Components::ColliderComponent2D&
SnakeSegment::GetColliderComponent()
{
  return *this->GetComponent<Physics::Collision::Components::ColliderComponent2D>();
}

[[nodiscard]] const Core::Rendering::Components::IRenderComponent2D&
SnakeSegment::GetRendererComponent2D() const
{
  return *this->GetComponent<Core::Rendering::Components::IRenderComponent2D>();
}

[[nodiscard]] const Physics::Collision::Components::ColliderComponent2D&
SnakeSegment::GetColliderComponent() const
{
  return *this->GetComponent<Physics::Collision::Components::ColliderComponent2D>();
}

}  // namespace SnakeGame
