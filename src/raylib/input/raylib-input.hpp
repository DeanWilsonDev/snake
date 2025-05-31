//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once

#include "../../platform/input/iinput.hpp"

namespace RaylibAdapter::Input {
class RaylibInput final : public Platform::Input::IInput {
 public:
  RaylibInput();
  ~RaylibInput() override = default;
  bool IsKeyPressed(Platform::Input::KeyCode keyCode) override;
  bool IsKeyDown(Platform::Input::KeyCode keyCode) override;

 private:
  static int MapKeyCode(Platform::Input::KeyCode keyCode);
};

}  // namespace RaylibAdapter::Input
