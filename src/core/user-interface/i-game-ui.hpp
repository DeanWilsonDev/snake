//
// Created by Dean Wilson on 26/7/2025.
//

#pragma once

#include "core/debug/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include "core/rendering/components/i-render-component-ui.hpp"

namespace Core {

namespace Rendering {
namespace Components {
class IRenderComponentUI;
}
}  // namespace Rendering

namespace UserInterface {
class IGameUI : public IUpdatable, public Debug::IDebugable {
 public:
  virtual ~IGameUI() = default;

  virtual void OnDrawUI() = 0;
  virtual void OnDebugDrawUI() {};

  [[nodiscard]] virtual Rendering::Components::IRenderComponentUI& GetRenderComponentUI() const = 0;
};
}  // namespace UserInterface
}  // namespace Core
