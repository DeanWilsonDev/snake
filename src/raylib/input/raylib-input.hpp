//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once

#include "../../platform/input/iinput.hpp"

namespace RaylibAdapter::Input {
class RaylibInput : public Platform::Input::IInput {
 public:
  RaylibInput();
  ~RaylibInput() = delete;
  static bool IsKeyPressed(int keyCode);
  static bool IsKeyDown(int keyCode);
private:
  static int MapKeyCode(int keyCode);
};

}  // namespace RaylibAdapter::Input
