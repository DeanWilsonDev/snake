//
// Created by Dean Wilson on 22/9/2025.
//

#pragma once

#include "core/spatial/components/i-transform-component.hpp"
#include "core/math/vector-2d.hpp"
#include "core/spatial/i-size-2d.hpp"
#include "engine/spatial/transform-2d.hpp"
#include "engine/spatial/size-2d.hpp"

namespace Engine::Spatial::Components {

class TransformComponent2D final : public Core::Spatial::Components::ITransformComponent2D {
 public:
  Core::Math::Vector2D position = Core::Math::Vector2D::Zero();
  // rotation is a float because in 2D you only need to rotate around the z axis.
  // there is no gimbal lock in 2D, so anything more than a float is overkill.
  float rotation{};
  Engine::Spatial::Size2D scale = Engine::Spatial::Size2D::Zero();

  TransformComponent2D(
      Core::Math::Vector2D position, float rotation, Engine::Spatial::Size2D scale
  );
  explicit TransformComponent2D(const Engine::Spatial::Transform2D& transform);

  TransformComponent2D();

  virtual void Update(const float deltaTime) override;

  [[nodiscard]] Core::Math::Vector2D& GetPosition() override { return this->position; }
  [[nodiscard]] float& GetRotation() override { return this->rotation; };
  [[nodiscard]] Engine::Spatial::Size2D& GetScale() override { return this->scale; };

  [[nodiscard]] const Core::Math::Vector2D& GetPosition() const override { return this->position; }
  [[nodiscard]] const float& GetRotation() const override { return this->rotation; };
  [[nodiscard]] const Engine::Spatial::Size2D& GetScale() const override { return this->scale; };

  void SetPosition(const Core::Math::Vector2D value) override { this->position = value; }
  void SetRotation(const float value) override { this->rotation = value; };
  void SetScale(const Core::Spatial::ISize2D& value) override { this->scale = value; };
};

}  // namespace Engine::Spatial::Components
