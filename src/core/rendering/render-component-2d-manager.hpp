//
// Created by Dean Wilson on 29/5/2025.
//

#pragma once

#include <vector>
#include "core/rendering/i-render-manager.hpp"

namespace Core {

namespace Rendering {
class IRenderable;
class IRenderer;

namespace Components {
class IRenderComponent2D;
}

class RenderComponent2DManager final : public IRenderManager {
 public:
  explicit RenderComponent2DManager();
  ~RenderComponent2DManager() = default;
  void Register(Components::IRenderComponent* component);
  void Unregister(Components::IRenderComponent* component);
  void Render(const IRenderer& renderer) const;

 private:
  std::vector<Components::IRenderComponent*> renderComponents;
};
}  // namespace Rendering
};  // namespace Core
