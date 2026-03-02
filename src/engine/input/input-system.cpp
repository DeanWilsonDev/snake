#include "engine/input/input-system.hpp"
#include "engine/input/input-action.hpp"
#include "engine/input/key-code.hpp"
#include "platform/input/i-input-backend.hpp"
#include <cstddef>

namespace Engine::Input {
using KeyCode = Engine::Input::KeyCode;

InputSystem::InputSystem(Platform::Input::IInputBackend& inputBackend) : inputBackend(inputBackend)
{
}

void InputSystem::SetKeyMap(const KeyMap& map)
{
  this->keyMap = map;
}

bool InputSystem::IsActionPressed(const Action action) const
{
  for (KeyCode keyCode : this->keyMap[static_cast<size_t>(action)]) {
    if (this->inputBackend.IsKeyPressed(keyCode)) {
      return true;
    }
  }
  return false;
}

bool InputSystem::IsActionDown(const Action action) const
{
  for (KeyCode keyCode : this->keyMap[static_cast<size_t>(action)]) {
    if (this->inputBackend.IsKeyDown(keyCode)) {
      return true;
    }
  }
  return false;
}

bool InputSystem::IsActionReleased(const Action action) const
{
  for (KeyCode keyCode : this->keyMap[static_cast<size_t>(action)]) {
    if (this->inputBackend.IsKeyReleased(keyCode)) {
      return true;
    }
  }
  return false;
}

}  // namespace Engine::Input
