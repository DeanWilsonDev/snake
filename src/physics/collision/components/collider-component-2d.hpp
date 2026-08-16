//
// Created by Dean Wilson on 29/6/2025.
//

#pragma once

#include <memory>
#include "core/components/i-collision-component-2d.hpp"
#include "core/spatial/i-transform-2d.hpp"
#include "physics/collision/rectangle-collider-2d.hpp"

namespace Physics::Collision::Components {

struct ColliderComponentParams {
  Core::Spatial::ITransform2D* transform;
};

class ColliderComponent2D : public Core::Components::IColliderComponent2D {
 public:
  explicit ColliderComponent2D(const ColliderComponentParams& params);

  virtual void BeginPlay() override;
  void Update(const float) override;

  void DebugUpdate() const override;
  void DebugRender() const override;

  [[nodiscard]] bool Intersects(const IColliderComponent2D& other) const override;
  [[nodiscard]] Physics::Collision::RectangleCollider2D& GetCollider() const override
  {
    return *this->collider;
  }

 private:
  Core::Spatial::ITransform2D* transform;
  std::unique_ptr<Physics::Collision::RectangleCollider2D> collider;
};
}  // namespace Physics::Collision::Components
