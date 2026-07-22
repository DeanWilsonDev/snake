//
// Created by Dean Wilson on 2nd February 2026
//

#pragma once

#include "core/input/key-code.hpp"

namespace Core::Input {

using KeyCode = Core::Input::KeyCode;

class IInputBackend {
 public:
  virtual ~IInputBackend() = default;
  virtual bool IsKeyDown(KeyCode keyCode) = 0;
  virtual bool IsKeyPressed(KeyCode keyCode) = 0;
  virtual bool IsKeyReleased(KeyCode keyCode) = 0;
};
}  // namespace Core::Input
