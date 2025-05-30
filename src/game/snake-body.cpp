#include "../snake-body.h"
#include "log.h"

namespace Game {

Rectangle SnakeBody::getBounds()
{
  this->bounds.x = this->position.x;
  this->bounds.y = this->position.y;
  this->bounds.width = this->size;
  this->bounds.height = this->size;
  return this->bounds;
};

void SnakeBody::move(Vector2 newPosition)
{
  this->position.x = newPosition.x;
  this->position.y = newPosition.y;
  LOG_DEBUG(
      "Body part at index {} has new position ({}, {})",
      this->index,
      this->position.x,
      this->position.y
  );
}
}  // namespace Game
