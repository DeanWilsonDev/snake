//
// Created by Dean Wilson on 29/5/2025.
//

#include "render-component-2d-manager.hpp"
#include "core/rendering/components/i-render-component-2d.hpp"
#include "core/rendering/components/i-render-component.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/logging/log.hpp"
#include <cassert>

namespace Renderer2D {

RenderComponent2DManager::RenderComponent2DManager() {}

void RenderComponent2DManager::Register(Core::Rendering::Components::IRenderComponent* component)
{
  if (auto component2d =
          dynamic_cast<Core::Rendering::Components::IRenderComponent2D*>(component)) {
    this->renderComponents.push_back(component2d);
  }
}

void RenderComponent2DManager::Unregister(Core::Rendering::Components::IRenderComponent* component)
{
  if (auto component2d =
          dynamic_cast<Core::Rendering::Components::IRenderComponent2D*>(component)) {
    std::erase(this->renderComponents, component2d);
    return;
  }
  LOG_CORE_ERROR("[RenderComponent2DManager] Component set to nullptr, cannot Unregister");
}

void RenderComponent2DManager::OnRender(const Core::Rendering::IRenderer& renderer) const
{
  if (this->renderComponents.empty()) {
    LOG_CORE_ERROR("[RenderComponent2DManager] No render components set");
    return;
  }

  for (Core::Rendering::Components::IRenderComponent* component : this->renderComponents) {
    if (component->GetActive()) {
      component->Render(renderer);
    }
  }
}
}  // namespace Renderer2D
