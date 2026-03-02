#pragma once

#include "engine/input/key-code.hpp"

namespace Platform::Input {

using KeyCode = Engine::Input::KeyCode;

class IInputBackend {
 public:
  virtual ~IInputBackend() = default;
  virtual bool IsKeyDown(KeyCode keyCode) = 0;
  virtual bool IsKeyPressed(KeyCode keyCode) = 0;
  virtual bool IsKeyReleased(KeyCode keyCode) = 0;
};
}  // namespace Platform::Input
