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
  if (!IsInitialized()) {
    return nullptr;
  }
  return backend->IsKeyPressed(keyCode);
}

bool InputManager::IsKeyDown(const KeyCode keyCode)
{
  if (!IsInitialized()) {
    return nullptr;
  }
  return backend->IsKeyDown(keyCode);
}
bool InputManager::IsInitialized()
{
  return backend != nullptr || throw std::runtime_error("Input backend is not initialized!");
}

}  // namespace Platform::Input
