//
// Created by Dean Wilson on 31/5/2025.
//

#include "raylib-input.hpp"
#include "raylib.h"

RaylibAdapter::Input::RaylibInput::RaylibInput() = default;

bool RaylibAdapter::Input::RaylibInput::IsKeyPressed(const int keyCode)
{
  return ::IsKeyPressed(MapKeyCode(keyCode));
}

bool RaylibAdapter::Input::RaylibInput::IsKeyDown(const int keyCode)
{
  return ::IsKeyDown(MapKeyCode(keyCode));
}

int RaylibAdapter::Input::RaylibInput::MapKeyCode(const int keyCode)
{
  using KeyCode = Platform::Input::KeyCode;

  switch (keyCode) {
    case KeyCode::KEY_A:
      return KEY_A;
    case KeyCode::KEY_D:
      return KEY_D;
    case KeyCode::KEY_S:
      return KEY_S;
    case KeyCode::KEY_W:
      return KEY_W;
    case KeyCode::KEY_ENTER:
      return KEY_ENTER;
    default:
      return 0;
  }
}