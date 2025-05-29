//
// Created by Dean Wilson on 29/5/2025.
//
#include "entity.h"
#include "../render-2d/irenderable.h"

namespace Core {
Entity::Entity(Component::IRenderable* renderComponent = nullptr)
    : renderComponent(renderComponent)
{
}

Entity::~Entity() = default;

void Entity::Update() {}

Component::IRenderable* Entity::GetRenderComponent() const
{
  return this->renderComponent;
}
}  // namespace Core
