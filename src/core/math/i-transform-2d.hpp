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

  virtual const Vector2D& GetPosition() const = 0;
  virtual const float& GetRotation() const = 0;
  virtual const Size2D& GetScale() const = 0;

  virtual void SetPosition(const Math::Vector2D value) = 0;
  virtual void SetRotation(const float value) = 0;
  virtual void SetScale(const Math::Size2D& value) = 0;
};

}  // namespace Core::Math
