//
// Created by Dean Wilson on 22/9/2025.
//

#pragma once
#include "core/spatial/i-size-2d.hpp"
#include "core/math/vector-2d.hpp"

namespace Core::Spatial {

class ITransform2D {
 public:
  virtual ~ITransform2D() = default;
  virtual Core::Math::Vector2D& GetPosition() = 0;
  virtual float& GetRotation() = 0;
  virtual ISize2D& GetScale() = 0;

  virtual const Math::Vector2D& GetPosition() const = 0;
  virtual const float& GetRotation() const = 0;
  virtual const ISize2D& GetScale() const = 0;

  virtual void SetPosition(const Math::Vector2D value) = 0;
  virtual void SetRotation(const float value) = 0;
  virtual void SetScale(const ISize2D& value) = 0;
};

}  // namespace Core::Spatial
