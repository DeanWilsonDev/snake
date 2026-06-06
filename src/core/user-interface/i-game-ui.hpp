//
// Created by Dean Wilson on 26/7/2025.
//

#pragma once

namespace Core {
namespace UserInterface {
class IUserInterface;
}  // namespace UserInterface

namespace Rendering {
namespace Components {
class IRenderComponentUI;
}
}  // namespace Rendering

namespace UserInterface {
class IGameUI {
 public:
  virtual ~IGameUI() = default;

  virtual void OnDrawUI(const Core::UserInterface::IUserInterface& ui) const = 0;

  // [[nodiscard]] virtual Rendering::Components::IRenderComponentUI& GetRenderComponentUI() const = 0;
};
}  // namespace UserInterface
}  // namespace Core
