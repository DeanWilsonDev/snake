//
// Created by Dean Wilson on 22/9/2025.
//

#pragma once
#include "size-2d.hpp"
#include "vector-2d.hpp"

namespace Core::Math {

class ITransform2D {
public:
  virtual ~ITransform2D() = default;
  virtual Vector2D& GetPosition() = 0;
  virtual float& GetRotation() = 0;
  virtual Size2D& GetScale() = 0;
};

}  // namespace Core::Math