#pragma once

#include "raylib.h"
#include "iostream"

class SnakeBody {
 public:
  SnakeBody(int index, Vector2 position, float size)
      : index(index), position(position), bounds(getBounds()), size(size)
  {
    DEBUG_ENABLED&& std::cout << "Creating SnakeBody with index: " << this->index
                              << " at position (" << this->position.x << ", " << this->position.y
                              << ")" << std::endl;
  }

  Rectangle getBounds();

  int index;
  Vector2 position;
  Rectangle bounds;
  float size;
};
