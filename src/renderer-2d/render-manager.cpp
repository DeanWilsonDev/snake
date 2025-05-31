//
// Created by Dean Wilson on 29/5/2025.
//

#include "render-manager.hpp"
#include "components/irender-component-2d.h"

namespace Renderer2D {

RenderManager::RenderManager(IRenderer& renderer) : renderer(renderer) {}

void RenderManager::Register(Component::IRenderComponent2D* component)
{
  if (!component) {
    return;
  }
  this->renderComponents.push_back(component);
}

void RenderManager::Unregister(Component::IRenderComponent2D* component)
{
  if (!component) {
    return;
  }
  std::erase(this->renderComponents, component);
}

void RenderManager::RenderAll() const
{
  for (auto* component : this->renderComponents) {
    component->Render(this->renderer);
  }
}
}  // namespace Renderer2D
