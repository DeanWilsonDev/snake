//
// Created by Dean Wilson on 6/6/2026.
//

#pragma once

#include "core/debug/i-debug-game-ui.hpp"
#include "core/debug/i-debug-user-interface-manager.hpp"
#include "core/debug/i-debug-user-interface.hpp"

#include <vector>

using namespace Core::Debug;

namespace Core {
namespace Debug {
class IDebugGameUI;
class IDebugUserInterface;
}  // namespace Debug
}  // namespace Core

namespace Engine {

namespace Math {
struct Vector2D;
}

namespace Rendering {
class IRenderer;
}
}  // namespace Engine

namespace Debug {
namespace UserInterface {

class DebugUserInterfaceManager final : public IDebugUserInterfaceManager {
 public:
  explicit DebugUserInterfaceManager();
  ~DebugUserInterfaceManager();

  // SIDE QUEST: Setup Get UI by name for both interface managers
  // [[nodiscard]] IDebugGameUI* GetDebugGameUIByName(std::string name) const override;

  void Register(IDebugGameUI* debugGameUI) override;
  void Unregister(IDebugGameUI* debugGameUI) override;

  void DebugDrawUI(const IDebugUserInterface& debugUI) const override;

 private:
  std::vector<IDebugGameUI*> debugGameUIs;
};
}  // namespace UserInterface
}  // namespace Debug
