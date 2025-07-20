#include "log.h"
#include "physics/components/collider-component-2d.hpp"
#include "game/game-objects/snake-segment.hpp"

namespace Game {

SnakeSegment::SnakeSegment(const SnakeSegmentParams& props)
    : index(props.index), transform(props.transform)
{
  auto bounds = Core::Math::Geometry::Rectangle(props.transform);
  const auto colliderParams =
      Physics::Components::ColliderComponentParams{.bounds = bounds, .transform = props.transform};
  this->colliderComponent = new Physics::Components::ColliderComponent2D(colliderParams);
}
SnakeSegment::~SnakeSegment()
{
  delete colliderComponent;
}

SnakeSegment* SnakeSegment::Initialize(const int index, const Core::Math::Transform2D& transform)
{
  LOG_TRACE("[SnakeSegment] Initializing New Snake Segment");

  this->index = index;
  this->transform = transform;

  LOG_TRACE(
      "[SnakeSegment] Creating SnakeBody with index: {} at position (({},{})), with a scale of "
      "(({}, {}))",
      this->index,
      this->transform.position.x,
      this->transform.position.y,
      this->transform.scale.x,
      this->transform.scale.y
  );
  return this;
};

void SnakeSegment::Move(Core::Math::Vector2D newPosition)
{
  LOG_TRACE("[SnakeSegment] Initializing New Snake Segment");
  this->transform.position.x = newPosition.x;
  this->transform.position.y = newPosition.y;
  LOG_TRACE(
      "[SnakeSegment] Segment at index {} has new position ({}, {})",
      this->index,
      this->transform.position.x,
      this->transform.position.y
  );
}
}  // namespace Game
