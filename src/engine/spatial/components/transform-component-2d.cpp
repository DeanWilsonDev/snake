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

TransformComponent2D::TransformComponent2D() = default;

}  // namespace Engine::Spatial::Components
