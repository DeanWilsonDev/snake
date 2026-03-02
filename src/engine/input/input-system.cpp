#include "engine/input/input-system.hpp"
#include "engine/input/input-action.hpp"
#include "engine/input/key-code.hpp"
#include "platform/input/i-input-backend.hpp"
#include <vector>
#include <array>

namespace Engine::Input {
using KeyCode = Engine::Input::KeyCode;

InputSystem::InputSystem(Platform::Input::IInputBackend& inputBackend) : inputBackend(inputBackend)
{
}

void InputSystem::SetKeyMap(const KeyMap& map)
{
  this->keyMap = map;
}

bool InputSystem::IsActionPressed(const Action action)
{
  for (KeyCode keyCode : this->keyMap[action]) {
    if (this->inputBackend.IsKeyPressed(keyCode)) {
      return true;
    }
  }
  return false;
}

bool InputSystem::IsActionDown(const Action action) {}

bool InputSystem::IsActionReleased(const Action action) {}

}  // namespace Engine::Input
