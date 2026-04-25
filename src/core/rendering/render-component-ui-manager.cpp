//
// Created by Dean Wilson on 29/5/2025.
//

#include "render-component-ui-manager.hpp"
#include "core/rendering/components/i-render-component-ui.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/logging/log.hpp"

#include <memory>
#include <utility>
#include <cassert>

namespace Core::Rendering {

RenderComponentUIManager::RenderComponentUIManager() {}

void RenderComponentUIManager::Register(std::unique_ptr<Components::IRenderComponentUI> component)
{
  if (!component) {
    return;
  }
  this->renderComponents.push_back(std::move(component));
}

void RenderComponentUIManager::Unregister(std::unique_ptr<Components::IRenderComponentUI> component)
{
  if (!component) {
    LOG_CORE_ERROR("[RenderComponentUIManager] Component set to nullptr, cannot Unregister");
    return;
  }
  std::erase(this->renderComponents, component);
}

void RenderComponentUIManager::Render(const IRenderer& renderer) const
{
  if (this->renderComponents.empty()) {
    LOG_CORE_ERROR("[RenderComponentUIManager] No render components set");
    return;
  }

  for (const std::unique_ptr<Components::IRenderComponentUI>& component : this->renderComponents) {
    if (!component) {
      continue;
    }
    if (component->GetActive()) {
      component->Render(renderer);
    }
  }
}
}  // namespace Core::Rendering
