//
// Created by Dean Wilson on 29/5/2025.
//

#include "render-component-2d-manager.hpp"
#include "components/i-render-component-2d.h"
#include <umbra/log.h>

#include <cassert>

namespace Renderer2D {

RenderComponent2DManager::RenderComponent2DManager(const std::shared_ptr<IRenderer>& renderer)
    : renderer(renderer)
{
  assert(renderer);
}

void RenderComponent2DManager::Register(Component::IRenderComponent2D* component)
{
  if (!component) {
    return;
  }
  this->renderComponents.push_back(component);
}

void RenderComponent2DManager::Unregister(Component::IRenderComponent2D* component)
{
  if (!component) {
    LOG_CORE_ERROR("[RenderComponent2DManager] Component set to nullptr, cannot Unregister");
    return;
  }
  std::erase(this->renderComponents, component);
}

void RenderComponent2DManager::RenderAll() const
{
  if (this->renderComponents.empty()) {
    LOG_CORE_ERROR("[RenderComponent2DManager] No render components set");
    return;
  }

  for (const auto* component : this->renderComponents) {
    if (!component) {
      return;
    }

    if (component->GetActive()) {
      component->Render(*this->renderer);
    }
  }
}
}  // namespace Renderer2D
