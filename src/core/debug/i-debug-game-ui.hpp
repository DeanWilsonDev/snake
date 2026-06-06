//
// Created by Dean Wilson on 6th June 2026
//

#pragma once

namespace Core {
namespace Debug {
class IDebugUserInterface;
}  // namespace Debug

namespace Rendering {
namespace Components {
class IRenderComponentUI;
}
}  // namespace Rendering

namespace Debug {
class IDebugGameUI {
 public:
  virtual ~IDebugGameUI() = default;

  virtual void OnDebugDrawUI(const Core::Debug::IDebugUserInterface& ui) const = 0;

  [[nodiscard]] virtual Rendering::Components::IRenderComponentUI& GetRenderComponentUI() const = 0;
};
}  // namespace Debug
}  // namespace Core
