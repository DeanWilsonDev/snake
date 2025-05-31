#pragma once
#include "../../core/iuser-interface.h"
#include "../../platform/window/config/window-config.h"
#include "log.h"

class Vector2;

namespace RaylibAdapter::UserInterface {
class RaylibUI : public Core::IUserInterface {
 public:
  explicit RaylibUI(Platform::Config::Window::WindowConfig windowConfig)
  {
    LOG_TRACE("Initializing Raylib User Interface");
  };
  static void DrawTextCentered(const char* text, Vector2 position, float fontSize);

 protected:
  Platform::Config::Window::WindowConfig windowConfig;
};

}  // namespace RaylibAdapter::UserInterface
