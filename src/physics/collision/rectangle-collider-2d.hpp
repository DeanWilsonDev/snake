#pragma once

#include "core/spatial/i-transform-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "engine/spatial/size-2d.hpp"
#include "core/geometry/rectangle.hpp"

namespace Physics::Collision {

using namespace Core::Math;
using namespace Core::Spatial;
using namespace Engine::Spatial;
using namespace Core::Geometry;

struct RectangleCollider2DParams {
  ITransform2D* transform{nullptr};
  Vector2D offset{0, 0};
  Size2D size{0, 0};
};

class RectangleCollider2D {
 public:
  ITransform2D* transform;
  Vector2D offset{0, 0};

  ///
  /// Override size of the bounding box
  ///
  Size2D size{0, 0};

  RectangleCollider2D(RectangleCollider2DParams params)
      : transform(params.transform), offset(params.offset), size(params.size)
  {
  }

  static bool Intersects(const Rectangle& a, const Rectangle& b)
  {
    return !(
        a.x + a.width <= b.x || a.x >= b.x + b.width || a.y + a.height <= b.y ||
        a.y >= b.y + b.height
    );
  }

  Rectangle GetWorldRect() const
  {
    const Vector2D position = transform->GetPosition();
    const Size2D scale = transform->GetScale();

    const float w = (size.width != 0) ? size.width : scale.width;
    const float h = (size.height != 0) ? size.height : scale.height;

    return Rectangle(position.x + offset.x, position.y + offset.y, w, h);
  }
};

}  // namespace Physics::Collision
