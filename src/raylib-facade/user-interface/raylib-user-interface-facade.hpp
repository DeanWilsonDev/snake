#pragma once
#include "core/iuser-interface.hpp"

class Vector2;

namespace RaylibFacade::UserInterface {
class RaylibUserInterfaceFacade : public Core::IUserInterface {
 public:
  explicit RaylibUserInterfaceFacade();
  static void DrawTextCentered(const char* text, Vector2 position, float fontSize);

 protected:
};

}  // namespace RaylibAdapter::UserInterface
