//
// Created by Dean Wilson on 29/6/2025.
//

#pragma once

#include "../../core/math/transform-2d.hpp"
#include "../../core/math/geometry/rectangle.h"

namespace Physics {
namespace Components {
class ColliderComponent2D {
 public:
  Core::Math::Transform2D transform;
  Core::Math::Geometry::Rectangle bounds;
};
}  // namespace Components
}  // namespace Physics
