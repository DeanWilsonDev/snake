//
// Created by Dean Wilson on 29/6/2025.
//

#pragma once

#include "core/components/i-component.hpp"
#include "core/math/transform-2d.hpp"
#include "core/math/geometry/rectangle.h"

namespace Physics::Components {

/**
 * @struct ColliderComponentParams
 * @brief Encapsulates the parameters required to initialize a 2D collider component.
 *
 * This structure provides references to the essential components required by a collider in a
 * 2D physics system. These include the transform to determine the collider's position, rotation,
 * and scale, and the bounds to define the geometry of the collider.
 *
 * @details
 * - `transform`: A reference to the `Transform2D` object representing the position, rotation,
 *    and scale of the collider.
 * - `bounds`: A reference to the `Rectangle` object representing the collider's geometric
 * boundaries.
 */
struct ColliderComponentParams {
  Core::Math::ITransform2D& transform;
  Core::Math::Geometry::Rectangle& bounds;
};

/**
 * @class ColliderComponent2D
 * @brief Represents a 2D collider component used in physics simulations.
 * This class provides functionality to manage and detect collisions between 2D objects.
 * It encapsulates a bounding rectangle for collision geometry and a reference
 * to the transform for position, scale, and rotation manipulation.
 * @details
 * - The `bounds` property defines the rectangular area of the collider.
 * - The `transform` property provides the spatial context of the collider, including position,
 * rotation, and scale.
 *
 * Responsibilities:
 * - Initialize the collider with parameters defined in `ColliderComponentParams`.
 * - Detect intersection with another collider via the `Intersects` method.
 */
class ColliderComponent2D: Core::Components::IComponent {
 public:
  explicit ColliderComponent2D(const ColliderComponentParams& params);
  [[nodiscard]] bool Intersects(const ColliderComponent2D& other) const;
  [[nodiscard]] Core::Math::Geometry::Rectangle GetBounds() const { return this->bounds;}

private:
  Core::Math::ITransform2D& transform;
  Core::Math::Geometry::Rectangle& bounds;
};
} // namespace Physics::Components

