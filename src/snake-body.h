#pragma once

#include "iostream"
#include "raylib.h"

class SnakeBody {
 public:
  SnakeBody(int index, Vector2 position, float size) : index(index), position(position), size(size)
  {
    this->bounds = getBounds();
    std::cout << "Creating SnakeBody with index: " << this->index << " at position ("
              << this->position.x << ", " << this->position.y << ")"
              << " with bounds: (" << this->bounds.x << ", " << this->bounds.y << ", "
              << this->bounds.height << ", " << this->bounds.width << ")" << std::endl;
  }

  Rectangle getBounds();

  int index;
  Vector2 position;
  Rectangle bounds;
  float size;
};
