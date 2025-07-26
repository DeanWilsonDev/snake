//
// Created by Dean Wilson on 29/5/2025.
//

#include "render-component-2d-manager.hpp"
#include "core.h"
#include "components/i-render-component-2d.h"
#include "log.h"
#include <utility>

#include <cassert>

namespace Renderer2D {

RenderComponent2DManager::RenderComponent2DManager(std::shared_ptr<IRenderer> renderer)
    : renderer(std::move(renderer))
{
  LOG_CORE_TRACE("[RenderComponent2DManager] Initializing");
  LOG_CORE_TRACE("[RenderComponent2DManager] Validating Dependencies");
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
    return;
  }
  std::erase(this->renderComponents, component);
}

void RenderComponent2DManager::RenderAll() const
{
  for (const auto* component : this->renderComponents) {
    component->Render(*this->renderer);
  }
}
}  // namespace Renderer2D
