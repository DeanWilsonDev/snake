//
// Created by Dean Wilson on 6th June 2026.
//

#pragma once

#include "core/components/i-component.hpp"
#include "physics/collision/rectangle-collider-2d.hpp"

namespace Core {
namespace Components {

class IColliderComponent2D : public Core::Components::IComponent {
 public:
  virtual ~IColliderComponent2D() = default;
  virtual bool Intersects(const IColliderComponent2D& other) const = 0;
  virtual Physics::Collision::RectangleCollider2D& GetCollider() const = 0;
};
}  // namespace Components
}  // namespace Core
