#include "snake.hpp"
#include <umbra/log.h>
#include "physics/components/collider-component-2d.hpp"
#include "game/game-objects/snake-segment.hpp"
#include "core/entity/entity.h"
#include "core/entity/game-entity.hpp"
#include "core/color.h"
#include "core/math/geometry/rectangle.h"
#include "core/math/vector-2d.hpp"
#include "renderer-2d/components/render-component-2d.h"

#include "core/components/transform-component-2d.hpp"

namespace Game {

SnakeSegment::SnakeSegment(const SnakeSegmentParams& params)
    : GameEntity(params), index(params.index)
{
  this->transform = new Core::Components::TransformComponent2D(params.initialTransform);

  this->bounds = new Core::Math::Geometry::Rectangle(*this->transform);

  const auto colliderParams =
      Physics::Components::ColliderComponentParams{.transform = *this->transform};

  this->colliderComponent = new Physics::Components::ColliderComponent2D(colliderParams);

  this->renderComponent = new Renderer2D::Component::RenderComponent2D(
      *this->transform, Core::COLOR_GREEN, this->Entity::GetActive()
  );
}

SnakeSegment::~SnakeSegment()
{
  if (this->colliderComponent) {
    delete colliderComponent;
    this->colliderComponent = nullptr;
  }

  if (this->renderComponent) {
    delete renderComponent;
    this->renderComponent = nullptr;
  }

  if (this->bounds) {
    delete bounds;
    this->bounds = nullptr;
  }

  if (this->transform) {
    delete transform;
    this->transform = nullptr;
  }
}

SnakeSegment* SnakeSegment::InitializeSnakeSegment(
    const int index, Core::Components::TransformComponent2D& transform
)
{
  LOG_TRACE("[SnakeSegment] Initializing New Snake Segment");

  this->index = index;
  this->transform = &transform;

  LOG_TRACE(
      "[SnakeSegment] Creating SnakeBody with index: {} at position {}, with a scale of {}",
      this->index,
      this->transform->position.ToString(),
      this->transform->scale.ToString()
  );
  return this;
};

void SnakeSegment::Move(const Core::Math::Vector2D newPosition)
{
  LOG_TRACE("[SnakeSegment] Initializing New Snake Segment");
  this->transform->position.x = newPosition.x;
  this->transform->position.y = newPosition.y;
  LOG_TRACE(
      "[SnakeSegment] Segment at index {} has new position {}",
      this->index,
      this->transform->position.ToString()
  );
}
}  // namespace Game
