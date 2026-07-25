#include "physics/collision/rectangle-collider-2d.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake.hpp"
#include "debug/debug.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/color/color.hpp"
#include "core/math/vector-2d.hpp"
#include "renderer-2d/components/render-component-2d.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"

namespace SnakeGame {

SnakeSegment::SnakeSegment(const SnakeSegmentParams& params) : Entity(params), index(params.index)
{
}

SnakeSegment::~SnakeSegment() {}

void SnakeSegment::OnRegistration()
{
  Entity::OnRegistration();

  const auto colliderParams =
      Physics::Collision::Components::ColliderComponentParams{.transform = this->transform};
  this->AddComponent<Physics::Collision::Components::ColliderComponent2D>(colliderParams);
  this->AddComponent<Renderer2D::Components::RenderComponent2D>(
      *this->transform, Core::Color::Green, this->GetActive()
  );
}

void SnakeSegment::Move()
{
  this->transform->GetPosition().x = this->direction.x;
  this->transform->GetPosition().y = this->direction.y;
}

void SnakeSegment::Update(const float deltaTime)
{
  this->accumulatedDistance += this->speed * deltaTime;

  this->Move();
  // this->CheckIfShouldGrow();  // MAIN QUEST: Implement a snake growth system
  accumulatedDistance -= this->size;
  // this->Teleport();  // MAIN QUEST: Implement a boundary detection system
}

void SnakeSegment::SetDirection(Core::Math::Vector2D value)
{
  this->direction = value;
  if (this->accumulatedDistance >= this->size) {
    if (this->direction.x != 0.0f || this->direction.y != 0.0f) {
      this->SetDirection(this->direction);
    }
  }
}

void SnakeSegment::DebugUpdate() const
{
  UMBRA_DEBUG(this->transform->GetScale().GetWidth(), "Snake/Segment-{}/Scale/Width", this->index);
  UMBRA_DEBUG(
      this->transform->GetScale().GetHeight(), "Snake/Segment-{}/Scale/Height", this->index
  );

  UMBRA_DEBUG(this->transform->GetPosition().x, "Snake/Segment-{}/Position/X", this->index);
  UMBRA_DEBUG(this->transform->GetPosition().y, "Snake/Segment-{}/Position/Y", this->index);
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
