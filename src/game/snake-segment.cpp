#include "snake-segment.hpp"
#include "log.h"

namespace Game {

SnakeSegment::SnakeSegment(const int index, const Core::Math::Transform2D& transform) : index(index), transform(transform){}

SnakeSegment* SnakeSegment::Initialize(const int index, const Core::Math::Transform2D& transform)
{
  LOG_TRACE("[SnakeSegment] Initializing New Snake Segment");

  this->index = index;
  this->transform = transform;

  LOG_TRACE(
      "[SnakeSegment] Creating SnakeBody with index: {} at position (({},{})), with a scale of (({}, {}))",
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
