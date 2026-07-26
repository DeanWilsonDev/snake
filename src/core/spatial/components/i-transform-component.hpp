//
// Created by Dean Wilson on 8th July 2026.
//

#pragma once
#include "core/components/i-component.hpp"
#include "core/spatial/i-transform-2d.hpp"

namespace Core::Spatial::Components {

class ITransformComponent2D : public Core::Components::IComponent,
                              public Core::Spatial::ITransform2D {
 public:
  ITransformComponent2D() = default;
  virtual ~ITransformComponent2D() = default;

  // Disable copying; implementations may allow moving
  ITransformComponent2D(const ITransformComponent2D&) = delete;
  ITransformComponent2D& operator=(const ITransformComponent2D&) = delete;
};

}  // namespace Core::Spatial::Components
