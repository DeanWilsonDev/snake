//
// Created by Dean Wilson on 22/9/2025.
//

#include "transform-component-2d.hpp"
#include "core/math/size-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "core/math/transform-2d.hpp"
#include "core/math/i-transform-2d.hpp"

namespace Engine::Spatial::Components {

TransformComponent2D::TransformComponent2D(
    const Math::Vector2D position, const float rotation, const Math::Size2D scale
)
    : position(position), rotation(rotation), scale(scale)
{
}

TransformComponent2D::TransformComponent2D(const Math::Transform2D& transform)
    : position(transform.position), rotation(transform.rotation), scale(transform.scale)
{
}

TransformComponent2D::TransformComponent2D(ITransform2D* transform)
    : position(transform != nullptr ? transform->GetPosition() : Core::Math::Vector2D::Zero())
    , rotation(transform != nullptr ? transform->GetRotation() : 0)
    , scale(transform != nullptr ? transform->GetScale() : Core::Math::Size2D::Zero()) {};

TransformComponent2D::TransformComponent2D() = default;

Math::ITransform2D& TransformComponent2D::GetTransform()
{
  static Math::Transform2D tempTransform(
      this->GetPosition(), this->GetRotation(), this->GetScale()
  );
  tempTransform.position = this->position;
  tempTransform.rotation = this->rotation;
  tempTransform.scale = this->scale;

  return tempTransform;
}

}  // namespace Core::Components
