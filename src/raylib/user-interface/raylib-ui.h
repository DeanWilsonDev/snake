#pragma once
#include "../../core/iuser-interface.h"
#include "log.h"

class Vector2;

namespace Raylib::UserInterface {
class RaylibUI : public Core::IUserInterface {
 public:
  RaylibUI() { LOG_TRACE("Initializing User Interface"); };
  static void DrawTextCentered(const char* text, Vector2 position, float fontSize);
};
}  // namespace Raylib::UserInterface
