//
// Created by Dean Wilson on 31/5/2025.
//
#pragma once
#include "iinput.hpp"
#include "core/implementation-manager.hpp"

namespace Platform::Input {

class InputManager final : public Core::ImplementationManager<IInput>{
  public:
  static bool IsKeyPressed(KeyCode keyCode);
  static bool IsKeyDown(KeyCode keyCode);
};
} // Input
// Platform
