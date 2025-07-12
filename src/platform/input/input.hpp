//
// Created by Dean Wilson on 28/6/2025.
//

#pragma once
#include "iinput.hpp"
#include "input-manager.hpp"

namespace Platform::Input {
class InputManager;
}
namespace Platform::Input {

class Input {
 public:
  static bool IsKeyDown(const KeyCode keyCode) { return InputManager::IsKeyDown(keyCode); }
  static bool IsKeyPressed(const KeyCode keyCode)
  {
    return InputManager::IsKeyPressed(keyCode);
  }
};
}  // namespace Platform::Input;