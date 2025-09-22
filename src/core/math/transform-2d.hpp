//
// Created by Dean Wilson on 1/6/2025.
//

#pragma once
#include "i-transform-2d.hpp"
#include "vector-2d.hpp"
#include "size-2d.hpp"

namespace Core::Math {
struct Transform2D final : public ITransform2D {
 public:
  Vector2D position;
  // rotation is a float because in 2D you only need to rotate around the z axis.
  // there is no gimbal lock in 2D, so anything more than a float is overkill.
  float rotation;
  Size2D scale = Size2D::Zero();

  Transform2D(const Vector2D position, const float rotation, const Size2D scale)
      : position(position), rotation(rotation), scale(scale) {};

  Transform2D(ITransform2D& transform)
      : position(transform.GetPosition()), rotation(transform.GetRotation()), scale(GetScale()) {};

  ~Transform2D() override = default;

  static Transform2D Empty();
  [[nodiscard]] Vector2D& GetPosition() override { return this->position; };
  [[nodiscard]] float& GetRotation() override { return this->rotation; };
  [[nodiscard]] Size2D& GetScale() override { return this->scale; };
};

inline Transform2D Transform2D::Empty()
{
  return {Vector2D::Zero(), 0.0f, Size2D::Zero()};
}
}  // namespace Core::Math
