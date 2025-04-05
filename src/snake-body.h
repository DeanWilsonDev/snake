#pragma once

#include "log.h"
#include "raylib.h"

class SnakeBody {
 public:
  SnakeBody(int index, Vector2 position, float size) : index(index), position(position), size(size)
  {
    this->bounds = getBounds();

    LOG_TRACE(
        "Creating SnakeBody with index: {} at position (({},{})), with bounds (({}, {}))",
        this->index,
        this->position.x,
        this->position.y,
        this->bounds.height,
        this->bounds.width
    );
  }

  Rectangle getBounds();
  void move(Vector2 newPosition);

  int index;
  Vector2 position;
  Rectangle bounds;
  float size;
};
