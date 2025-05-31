//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once

#include "../../platform/input/iinput.hpp"

namespace RaylibAdapter::Input {
class RaylibInputAdapter final : public Platform::Input::IInput {
 public:
  RaylibInputAdapter();
  ~RaylibInputAdapter() override = default;
  bool IsKeyPressed(Platform::Input::KeyCode keyCode) override;
  bool IsKeyDown(Platform::Input::KeyCode keyCode) override;

 private:
  static int MapKeyCode(Platform::Input::KeyCode keyCode);
};

}  // namespace RaylibAdapter::Input
