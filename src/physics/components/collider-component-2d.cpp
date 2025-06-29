//
// Created by Dean Wilson on 29/6/2025.
//

#include "collider-component-2d.hpp"
Physics::Components::ColliderComponent2D::ColliderComponent2D(const ColliderComponentParams& params): transform(params.transform), bounds(params.bounds) {}