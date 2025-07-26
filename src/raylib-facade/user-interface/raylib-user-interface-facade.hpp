#pragma once
#include "core/entity.h"
#include "user-interface/i-user-interface.hpp"

class Vector2;

namespace RaylibFacade::UserInterface {
class RaylibUserInterfaceFacade final: public ::UserInterface::IUserInterface {
 public:
  explicit RaylibUserInterfaceFacade();
  void DrawTextCentered(const char* text, Core::Math::Vector2D position, float fontSize) override;
};

}  // namespace RaylibAdapter::UserInterface
