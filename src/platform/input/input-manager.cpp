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
      LOG_CORE_FATAL("Input Manager has not been initialized");
      return false;
    }
    return backend->IsKeyPressed(keyCode);
  }
  catch (const std::exception& e) {
    LOG_CORE_FATAL("Error calling IsKeyDown {}", e.what());
    throw;
  }
}

bool InputManager::IsKeyDown(const KeyCode keyCode)
{
  try {
    if (IsInitialized()) {
      return backend->IsKeyDown(keyCode);
    }
    LOG_CORE_FATAL("Input Manager has not been initialized");
    return false;
  }
  catch (const std::exception& e) {
    LOG_CORE_FATAL("Error calling IsKeyDown {}", e.what());
    throw;
  }
}
}  // namespace Platform::Input
