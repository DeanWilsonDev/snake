//
// Created by Dean Wilson on 29/6/2025.
//

#include "memory"
#include "collider-component-2d.hpp"
#include <cassert>
#include "physics/collision/rectangle-collider-2d.hpp"

Physics::Collision::Components::ColliderComponent2D::ColliderComponent2D(
    const ColliderComponentParams& params
)
    : transform(params.transform)
{
  assert(this->transform != nullptr && "ColliderComponent2D requires a valid transform");
  RectangleCollider2DParams rectangleParams = {.transform = this->transform};
  this->collider = std::make_unique<Physics::Collision::RectangleCollider2D>(rectangleParams);
}

bool Physics::Collision::Components::ColliderComponent2D::Intersects(
    const IColliderComponent2D& other
) const
{
  return RectangleCollider2D::Intersects(
      this->collider->GetWorldRect(), other.GetCollider().GetWorldRect()
  );
}
