//
// Created by Dean Wilson on 29/5/2025.
//

#pragma once

#include <vector>
#include "core/rendering/i-render-component-manager.hpp"

namespace Core::Rendering {
class IRenderable;
}

namespace Core::Rendering {
class IRenderer;
}

namespace Core::Rendering::Components {
class IRenderComponent2D;
}  // namespace Core::Rendering::Components

namespace Renderer2D {

// RAID BOSS: Move this entire Manager into a pipeline in the ECS
class RenderComponent2DManager final : public Core::Rendering::IRenderComponentManager {
 public:
  explicit RenderComponent2DManager();
  ~RenderComponent2DManager() = default;
  void Register(Core::Rendering::Components::IRenderComponent* component) override;
  void Unregister(Core::Rendering::Components::IRenderComponent* component) override;
  void OnRender(const Core::Rendering::IRenderer& renderer) const override;

 private:
  std::vector<Core::Rendering::Components::IRenderComponent*> renderComponents;
};
}  // namespace Renderer2D
