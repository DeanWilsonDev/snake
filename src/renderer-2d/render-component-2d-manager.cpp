//
// Created by Dean Wilson on 29/5/2025.
//

#include "render-component-2d-manager.hpp"
#include "core.h"
#include "components/i-render-component-2d.h"
#include "log.h"

#include <cassert>

namespace Renderer2D {

RenderComponent2DManager::RenderComponent2DManager(const std::shared_ptr<IRenderer>& renderer)
    : renderer(renderer)
{
  LOG_CORE_TRACE("[RenderComponent2DManager] Initializing");
  LOG_CORE_TRACE("[RenderComponent2DManager] Validating Dependencies");
  LOG_CORE_TRACE("[RenderComponent2DManager] Renderer set to [{}]", static_cast<void*>(&*renderer));
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
    LOG_CORE_DEBUG("[RenderComponent2DManager] Component set to nullptr, cannot Unregister");
    return;
  }
  std::erase(this->renderComponents, component);
}

void RenderComponent2DManager::RenderAll() const
{
  LOG_CORE_TRACE("[RenderComponent2DManager] Begin rendering RenderComponent2D");
  if (this->renderComponents.size() == 0) {
    LOG_CORE_DEBUG("[RenderComponent2DManager] No render components set");
    return;
  }

  for (const auto* component : this->renderComponents) {
    LOG_CORE_DEBUG("[RenderComponentManager] Rendering component: [{}]", static_cast<void*>(&component));
    LOG_CORE_DEBUG("[RenderComponentManager] Renderer: [{}]", static_cast<void*>(&*this->renderer));

    if (!component) {
      LOG_CORE_TRACE("[RenderComponentManager] Component is a nullptr");
      return;
    }
    component->Render(*this->renderer);
  }
}
}  // namespace Renderer2D
