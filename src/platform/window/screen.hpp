//
// Created by Dean Wilson on 28/6/2025.
//

#ifndef SCREEN_HPP
#define SCREEN_HPP
#include "window-manager.hpp"

namespace Platform::Window {
class Screen {
 public:
  static int GetWidth() { return WindowManager::GetScreenWidth(); }
  static int GetHeight() { return WindowManager::GetScreenWidth(); }
};
}  // namespace Game

#endif  // SCREEN_HPP
