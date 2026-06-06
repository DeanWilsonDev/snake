//
// Created by Dean Wilson on 31/5/2025.
//

#include "raylib-input-backend-facade.hpp"

#include "core/input/key-code.hpp"
#include "raylib.h"

using KeyCode = Core::Input::KeyCode;

namespace RaylibFacade::Input {

RaylibInputBackendFacade::RaylibInputBackendFacade() = default;

bool RaylibInputBackendFacade::IsKeyPressed(const KeyCode keyCode)
{
  const bool pressed = ::IsKeyPressed(MapKeyCode(keyCode));
  return pressed;
}

bool RaylibInputBackendFacade::IsKeyDown(const KeyCode keyCode)
{
  return ::IsKeyDown(MapKeyCode(keyCode));
}

bool RaylibInputBackendFacade::IsKeyReleased(const KeyCode keyCode)
{
  return ::IsKeyReleased(MapKeyCode(keyCode));
}

int RaylibInputBackendFacade::MapKeyCode(const KeyCode keyCode)
{
  switch (keyCode) {
    case KeyCode::A:
      return KEY_A;
    case KeyCode::D:
      return KEY_D;
    case KeyCode::S:
      return KEY_S;
    case KeyCode::W:
      return KEY_W;
    case KeyCode::Enter:
      return KEY_ENTER;
    default:
      return 0;
  }
}
}  // namespace RaylibFacade::Input
