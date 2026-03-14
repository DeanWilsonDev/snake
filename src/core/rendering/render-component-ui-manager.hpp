//
// Created by Dean Wilson on 29/5/2025.
//

#pragma once

#include "core/rendering/i-render-manager.hpp"

#include <vector>
#include <memory>

namespace Core {

namespace Rendering {
class IRenderable;
class IRenderer;

namespace Components {
class IRenderComponentUI;
}

class RenderComponentUIManager final : public IRenderManager {
 public:
  explicit RenderComponentUIManager();
  ~RenderComponentUIManager() = default;
  void Register(std::unique_ptr<Components::IRenderComponentUI> component);
  void Unregister(std::unique_ptr<Components::IRenderComponentUI> component);
  void Render(const IRenderer& renderer) const;

 private:
  std::vector<std::unique_ptr<Components::IRenderComponentUI>> renderComponents;
};
}  // namespace Rendering
};  // namespace Core
