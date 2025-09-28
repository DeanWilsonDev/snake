//
// Created by Dean Wilson on 29/6/2025.
//

#include "collider-component-2d.hpp"

Physics::Components::ColliderComponent2D::ColliderComponent2D(const ColliderComponentParams& params)
    : transform(params.transform)
{
  this->bounds = new Core::Math::Geometry::Rectangle(this->transform);
}

bool Physics::Components::ColliderComponent2D::Intersects(const ColliderComponent2D& other) const
{
  return this->bounds->Intersects(*other.GetBounds());
}