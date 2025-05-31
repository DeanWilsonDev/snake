#pragma once
#include "../../core/iuser-interface.hpp"

class Vector2;

namespace RaylibAdapter::UserInterface {
class RaylibUserInterfaceAdapter : public Core::IUserInterface {
 public:
  explicit RaylibUserInterfaceAdapter();
  static void DrawTextCentered(const char* text, Vector2 position, float fontSize);

 protected:
};

}  // namespace RaylibAdapter::UserInterface
