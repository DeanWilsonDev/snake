#pragma once

#include "raylib.h"
#include "constants.h"
#include "iostream"

class SnakeBody {
 public:
  SnakeBody(int index, Vector2 position) : index(index), position(position), bounds(getBounds())
  {
    DEBUG_ENABLED&& std::cout << "Creating SnakeBody with index: " << this->index
                              << " at position (" << this->position.x << ", " << this->position.y
                              << ")" << std::endl;
  }

  Rectangle getBounds();

  int index;
  Vector2 position;
  Rectangle bounds;
  float size = DEFAULT_BOX_SIZE;
};
