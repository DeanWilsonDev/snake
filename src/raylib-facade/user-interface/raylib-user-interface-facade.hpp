#pragma once
#include "core/math/vector-2d.hpp"
#include "core/debug/i-debug-hud.hpp"
#include "user-interface/i-user-interface.hpp"

namespace Core::Math {
struct Vector2D;
}

namespace RaylibFacade::UserInterface {
class RaylibUserInterfaceFacade final : public ::UserInterface::IUserInterface {
 public:
  explicit RaylibUserInterfaceFacade();
  void DrawTextCentered(const char* text, Core::Math::Vector2D position, float fontSize) override;
  void RenderDebugHUD(const Core::Debug::IDebugHUD& debugHUD) override;
};

}  // namespace RaylibFacade::UserInterface
