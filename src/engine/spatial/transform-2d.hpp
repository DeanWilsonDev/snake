//
// Created by Dean Wilson on 1/6/2025.
//

#pragma once
#include "core/spatial/i-transform-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "core/spatial/i-size-2d.hpp"
#include "engine/spatial/size-2d.hpp"

namespace Engine::Spatial {
struct Transform2D final : public Core::Spatial::ITransform2D {
 public:

  Core::Math::Vector2D position;
  // rotation is a float because in 2D you only need to rotate around the z axis.
  // there is no gimbal lock in 2D, so anything more than a float is overkill.
  float rotation;
  Size2D scale = Size2D::Zero();

  Transform2D(const Core::Math::Vector2D position, const float rotation, const Size2D scale)
      : position(position), rotation(rotation), scale(scale) {};

  explicit Transform2D(ITransform2D& transform)
      : position(transform.GetPosition())
      , rotation(transform.GetRotation())
      , scale(transform.GetScale())
  {
  }

  Transform2D(const Transform2D& other)
      : position(other.position), rotation(other.rotation), scale(other.scale)
  {
  }

  // Allow moving to transfer ownership
  Transform2D(Transform2D&&) = default;
  Transform2D& operator=(Transform2D&&) = default;

  ~Transform2D() override = default;

  static Transform2D Empty();
  [[nodiscard]] Core::Math::Vector2D& GetPosition() override { return this->position; };
  [[nodiscard]] float& GetRotation() override { return this->rotation; };
  [[nodiscard]] Core::Spatial::ISize2D& GetScale() override { return this->scale; };

  [[nodiscard]] const Core::Math::Vector2D& GetPosition() const override { return this->position; };
  [[nodiscard]] const float& GetRotation() const override { return this->rotation; };
  [[nodiscard]] const Core::Spatial::ISize2D& GetScale() const override { return this->scale; };

  void SetPosition(const Core::Math::Vector2D value) override { this->position = value; }
  void SetRotation(const float value) override { this->rotation = value; };
  void SetScale(const Core::Spatial::ISize2D& value) override { this->scale = value; };
};

inline Transform2D Transform2D::Empty()
{
  return {Core::Math::Vector2D::Zero(), 0.0f, Size2D::Zero()};
}
}  // namespace Engine::Spatial
