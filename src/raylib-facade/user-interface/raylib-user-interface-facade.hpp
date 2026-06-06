#pragma once
#include "core/math/vector-2d.hpp"
#include "core/user-interface/i-user-interface.hpp"

namespace Core::Math {
struct Vector2D;
}

namespace RaylibFacade::UserInterface {
class RaylibUserInterfaceFacade final : public Core::UserInterface::IUserInterface {
 public:
  explicit RaylibUserInterfaceFacade();
  void DrawTextCentered(const char* text, Core::Math::Vector2D position, float fontSize) const override;
};

}  // namespace RaylibFacade::UserInterface
