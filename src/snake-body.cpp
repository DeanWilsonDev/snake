#include "snake-body.h"

Rectangle SnakeBody::getBounds()
{
  this->bounds.x = this->position.x;
  this->bounds.y = this->position.y;
  this->bounds.width = this->size;
  this->bounds.height = this->size;
  return this->bounds;
};
