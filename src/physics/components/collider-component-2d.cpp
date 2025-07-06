//
// Created by Dean Wilson on 29/6/2025.
//

#include "collider-component-2d.hpp"
Physics::Components::ColliderComponent2D::ColliderComponent2D(const ColliderComponentParams& params)
    : bounds(params.bounds), transform(params.transform)
{
}

bool Physics::Components::ColliderComponent2D::Intersects(const ColliderComponent2D& other) const
{
  return this->bounds.Intersects(other.bounds);
}