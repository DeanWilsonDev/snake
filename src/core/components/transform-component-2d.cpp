//
// Created by Dean Wilson on 22/9/2025.
//

#include "transform-component-2d.hpp"

namespace Core::Components {

TransformComponent2D::TransformComponent2D(
    const Math::Vector2D position, const float rotation, const Math::Size2D scale
): position(position), rotation(rotation), scale(scale) {
}

TransformComponent2D::TransformComponent2D(ITransform2D* transform)
      : position(transform->GetPosition()), rotation(transform->GetRotation()), scale(transform->GetScale()) {};

TransformComponent2D::TransformComponent2D() = default;

}  // namespace Core::Components