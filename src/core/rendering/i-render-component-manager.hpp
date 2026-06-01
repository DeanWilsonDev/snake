//
// Created by Dean Wilson on 3rd May 2026
//

#pragma once

#include "core/rendering/i-render-manager.hpp"

namespace Core {

namespace Rendering {
class IRenderer;

namespace Components {
class IRenderComponent2D;
}

class IRenderComponentManager : public Core::Rendering::IRenderManager {
 public:
  virtual ~IRenderComponentManager() = default;
  virtual void Register(Core::Rendering::Components::IRenderComponent* component) = 0;
  virtual void Unregister(Core::Rendering::Components::IRenderComponent* component) = 0;
  void OnRender(const Core::Rendering::IRenderer& renderer) const override = 0;
};

}  // namespace Rendering
};  // namespace Core
