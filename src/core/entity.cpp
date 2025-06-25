//
// Created by Dean Wilson on 29/5/2025.
//
#include "entity.h"
#include "raylib.h"
#include "../renderer-2d/irenderable.h"
#include "math/transform-2d.hpp"

namespace Core {
Entity::Entity(Component::IRenderable* renderComponent = nullptr)
    : transform(Transform), renderComponent(renderComponent)
{
}

Entity::~Entity() = default;

void Entity::Update() {}

Component::IRenderable* Entity::GetRenderComponent() const
{
  return this->renderComponent;
}
}  // namespace Core
