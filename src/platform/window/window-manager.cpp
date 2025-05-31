//
// Created by Dean Wilson on 31/5/2025.
//

#include "window-manager.hpp"

#include "iwindow.h"
#include "log.h"

namespace Platform::Window {

WindowManager::WindowManager() {}

void WindowManager::SetBackend(std::unique_ptr<IWindow> windowImpl)
{
  backend = std::move(windowImpl);
}

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

bool WindowManager::IsInitialized()
{
  return backend != nullptr || throw std::runtime_error("Window backend is not initialized!");
}

}  // namespace Platform::Window