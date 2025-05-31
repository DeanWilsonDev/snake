//
// Created by Dean Wilson on 31/5/2025.
//

#include "input-manager.hpp"

namespace Platform::Input {
void InputManager::SetBackend(std::unique_ptr<IInput> inputImpl)
{
  backend = std::move(inputImpl);
}

bool InputManager::IsKeyPressed(const KeyCode keyCode)
{
  return backend->IsKeyPressed(keyCode);
}

bool InputManager::IsKeyDown(const KeyCode keyCode)
{
  return backend->IsKeyDown(keyCode);
}

}  // namespace Platform::Input
// Platform