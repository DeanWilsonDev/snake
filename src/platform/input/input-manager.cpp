//
// Created by Dean Wilson on 31/5/2025.
//

#include "input-manager.hpp"

#include "core.h"
#include "log.h"

namespace Platform::Input {

bool InputManager::IsKeyPressed(const KeyCode keyCode)
{
  try {
    if (!IsInitialized()) {
      return nullptr;
    }
    return backend->IsKeyPressed(keyCode);
  }
  catch (const std::exception& e) {
    LOG_CORE_FATAL("Error calling IsKeyDown {}", e.what());
    throw;
  }
  return nullptr;
}

bool InputManager::IsKeyDown(const KeyCode keyCode)
{
  try {
    if (IsInitialized()) {
      return backend->IsKeyDown(keyCode);
    }
  }
  catch (const std::exception& e) {
    LOG_CORE_FATAL("Error calling IsKeyDown {}", e.what());
    throw;
  }
  return nullptr;
}
}  // namespace Platform::Input
