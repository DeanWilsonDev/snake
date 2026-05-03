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
}  // namespace Rendering
}  // namespace Core
   //

namespace Engine {
namespace UI {

class RenderComponentUIManager final : public Core::Rendering::IRenderManager {
 public:
  explicit RenderComponentUIManager();
  ~RenderComponentUIManager() = default;
  void Register(std::unique_ptr<Core::Rendering::Components::IRenderComponentUI> component);
  void Unregister(std::unique_ptr<Core::Rendering::Components::IRenderComponentUI> component);
  void OnRender(const Core::Rendering::IRenderer& renderer) const;

 private:
  std::vector<std::unique_ptr<Core::Rendering::Components::IRenderComponentUI>> renderComponents;
};
};  // namespace UI
}  // namespace Engine
