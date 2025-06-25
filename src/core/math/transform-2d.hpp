//
// Created by Dean Wilson on 1/6/2025.
//

#pragma once
#include "vector-2d.hpp"

namespace Core::Math {
struct Transform2D {
public:
  Transform2D(Vector2D position, float rotation, Vector2D scale);
  ~Transform2D() = default;

  Vector2D position;

  // rotation is a float because in 2D you only need to rotate around the z axis.
  // there is no gimbal lock in 2D, so anything more than a float is overkill.
  float rotation;
  Vector2D scale;
};
}

