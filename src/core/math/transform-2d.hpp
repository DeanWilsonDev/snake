//
// Created by Dean Wilson on 1/6/2025.
//

#pragma once
#include "vector-2d.hpp"
#include "size-2d.hpp"

namespace Core::Math {
struct Transform2D {
 public:
  /**
   *
   */
  Vector2D position;
  // rotation is a float because in 2D you only need to rotate around the z axis.
  // there is no gimbal lock in 2D, so anything more than a float is overkill.
  float rotation;
  Size2D scale = Size2D::Zero();

  Transform2D(const Vector2D position, const float rotation, const Size2D scale)
      : position(position), rotation(rotation), scale(scale) {};

  ~Transform2D() = default;

  static Transform2D Empty() { return {Vector2D::Zero(), 0.0f, Size2D::Zero()}; }
};
}  // namespace Core::Math
