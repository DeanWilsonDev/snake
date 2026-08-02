#include "engine/entities/entity.hpp"
#include "physics/collision/rectangle-collider-2d.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake-game/game-components/snake-body-component.hpp"
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

void SnakeSegment::BeginPlay()
{
  this->size = this->transform->GetScale().GetWidth();
}

void SnakeSegment::Step()
{
  if (this->pendingDirection.x != 0.0f || this->pendingDirection.y != 0.0f) {
    bool isReversal = this->pendingDirection.x == -this->direction.x &&
                      this->pendingDirection.y == -this->direction.y;
    if (!isReversal) {
      this->direction = this->pendingDirection;
    }
  }
  this->transform->GetPosition().x += this->direction.x * this->size;
  this->transform->GetPosition().y += this->direction.y * this->size;
}

void SnakeSegment::Update(const float deltaTime)
{
  this->moveTimer += deltaTime;
  if (this->moveTimer >= this->moveInterval) {
    this->moveTimer -= this->moveInterval;
    this->Step();
  }

  this->accumulatedDistance += this->speed * deltaTime;

  // this->CheckIfShouldGrow();  // MAIN QUEST: Implement a snake growth system
  accumulatedDistance -= this->size;
  // this->Teleport();  // MAIN QUEST: Implement a boundary detection system
}

void SnakeSegment::SetDirection(Core::Math::Vector2D value)
{
  this->pendingDirection = value;
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
