//
// Created by Dean Wilson on 31/5/2025.
//

#include "raylib-input-adapter.hpp"
#include "raylib.h"

namespace RaylibAdapter::Input {

RaylibInputAdapter::RaylibInputAdapter() = default;

bool RaylibInputAdapter::IsKeyPressed(const Platform::Input::KeyCode keyCode)
{
  return ::IsKeyPressed(MapKeyCode(keyCode));
}

bool RaylibInputAdapter::IsKeyDown(const Platform::Input::KeyCode keyCode)
{
  return ::IsKeyDown(MapKeyCode(keyCode));
}

int RaylibInputAdapter::MapKeyCode(const Platform::Input::KeyCode keyCode)
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
}  // namespace RaylibAdapter::Input
