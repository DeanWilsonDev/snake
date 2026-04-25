//
// Created by Dean Wilson on 31/5/2025.
//

#include "window-manager.hpp"

#include "i-window.h"
#include "core/logging/log.hpp"

namespace Platform::Window {

WindowManager::WindowManager() = default;

int WindowManager::GetScreenWidth()
{
  try {
    if (IsInitialized()) {
      return backend->GetScreenWidth();
    }
    return 0;
  }
  catch (const std::exception& e) {
    LOG_CORE_FATAL("Error getting screen width {}", e.what());
    throw;
  }
}

int WindowManager::GetScreenHeight()
{
  try {
    if (IsInitialized()) {
      return backend->GetScreenHeight();
    }
    return 0;
  }
  catch (const std::exception& e) {
    LOG_CORE_FATAL("Error getting screen height {}", e.what());
    throw;
  }
}
}  // namespace Platform::Window
