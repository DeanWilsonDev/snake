#pragma once
#include "core/entity.h"
#include "user-interface/iuser-interface.hpp"

class Vector2;

namespace RaylibFacade::UserInterface {
class RaylibUserInterfaceFacade : public ::UserInterface::IUserInterface {
 public:
  explicit RaylibUserInterfaceFacade();
  static void DrawTextCentered(const char* text, Core::Math::Vector2D position, float fontSize);
};

}  // namespace RaylibAdapter::UserInterface
