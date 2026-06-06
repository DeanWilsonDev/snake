#pragma once
#include "core/debug/i-debug-hud.hpp"
#include "core/debug/i-debug-user-interface.hpp"

namespace Core::Math {
struct Vector2D;
}

namespace RaylibFacade::UserInterface {
class RaylibDebugUserInterfaceFacade final : public Core::Debug::IDebugUserInterface {
 public:
  explicit RaylibDebugUserInterfaceFacade();
  void RenderDebugHUD(const Core::Debug::IDebugHUD& debugHUD) override;
};

}  // namespace RaylibFacade::UserInterface
