//
// Created by Dean Wilson on 22/9/2025.
//

#include "transform-component-2d.hpp"
#include "engine/spatial/size-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "engine/spatial/transform-2d.hpp"
#include "core/spatial/i-transform-2d.hpp"

namespace Engine::Spatial::Components {

TransformComponent2D::TransformComponent2D(
    Core::Math::Vector2D position, float rotation, Engine::Spatial::Size2D scale
)
    : position(position), rotation(rotation), scale(scale)
{
}

TransformComponent2D::TransformComponent2D(const Transform2D& transform)
    : position(transform.position), rotation(transform.rotation), scale(transform.scale)
{
}

TransformComponent2D::TransformComponent2D(ITransform2D* transform)
    : position(transform != nullptr ? transform->GetPosition() : Core::Math::Vector2D::Zero())
    , rotation(transform != nullptr ? transform->GetRotation() : 0)
    , scale(
          transform != nullptr ? Engine::Spatial::Size2D(transform->GetScale())
                               : Engine::Spatial::Size2D::Zero()
      ) {};

TransformComponent2D::TransformComponent2D() = default;

Core::Spatial::ITransform2D& TransformComponent2D::GetTransform()
{
  static Engine::Spatial::Transform2D tempTransform(
      this->GetPosition(), this->GetRotation(), this->GetScale()
  );
  tempTransform.position = this->position;
  tempTransform.rotation = this->rotation;
  tempTransform.scale = this->scale;

  return tempTransform;
}

}  // namespace Engine::Spatial::Components
