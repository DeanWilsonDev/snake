//
// Created by Dean Wilson on 31/5/2025.
//
#pragma once
#include "iinput.hpp"

#include <memory>

namespace Platform::Input {

class InputManager{
  public:
  static void SetBackend(std::unique_ptr<IInput> inputImpl);
  static bool IsKeyPressed(KeyCode keyCode);
  static bool IsKeyDown(KeyCode keyCode);

private:
  static bool IsInitialized();

  static std::unique_ptr<IInput> backend;
};

} // Input
// Platform
