//
// Created by Dean Wilson on 29/5/2025.
//

#include "../components/render-manager.h"

#include "irenderable.h"

RenderManager::RenderManager(IRenderer& renderer) : renderer(renderer) {}

void RenderManager::Register(Component::IRenderable* component)
{
  this->renderComponents.push_back(component);
}

void RenderManager::Unregister(Component::IRenderable* component)
{
  this->renderComponents.erase(
      std::remove(this->renderComponents.begin(), this->renderComponents.end(), component),
      this->renderComponents.end()
  );
}

void RenderManager::RenderAll() const
{
  for (auto* component : this->renderComponents) {
    component->Render(this->renderer);
  }
}
