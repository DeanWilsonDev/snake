//
// Created by Dean Wilson on 22/9/2025.
//

#pragma once
#include "i-component.hpp"
#include "core/math/transform-2d.hpp"
#include "core/math/i-transform-2d.hpp"
#include "core/math/size-2d.hpp"
#include "core/math/vector-2d.hpp"

namespace Core::Components {

class TransformComponent2D final : public IComponent, public Math::ITransform2D {
 public:
  Math::Vector2D position{};
  // rotation is a float because in 2D you only need to rotate around the z axis.
  // there is no gimbal lock in 2D, so anything more than a float is overkill.
  float rotation{};
  Math::Size2D scale = Math::Size2D::Zero();

  TransformComponent2D(Math::Vector2D position, float rotation, Math::Size2D scale);
  explicit TransformComponent2D(const Math::Transform2D& transform);

  explicit TransformComponent2D(ITransform2D* transform);

  TransformComponent2D();

  // Allow moving to transfer ownership
  TransformComponent2D(TransformComponent2D&&) = default;
  TransformComponent2D& operator=(TransformComponent2D&&) = default;

  [[nodiscard]] Math::Vector2D& GetPosition() override { return this->position; }
  [[nodiscard]] float& GetRotation() override { return this->rotation; };
  [[nodiscard]] Math::Size2D& GetScale() override { return this->scale; };
  [[nodiscard]] Math::Transform2D& GetTransform();
};

}  // namespace Core::Components
