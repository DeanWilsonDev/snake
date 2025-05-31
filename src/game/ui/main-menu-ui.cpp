//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-ui.hpp"

#include "raylib.h"
#include "../../platform/window/window-manager.hpp"

namespace Game {

MainMenuUI::MainMenuUI() {}

void MainMenuUI::Render()
{
  DrawTextCentered("Snake", (Vector2){Platform::Window::WindowManager::GetScreenWidth() / 2.0f, 40.0f}, 80);
  DrawTextCentered(
      "Press 'Enter' to start", (Vector2){Platform::Window::WindowManager::GetScreenWidth() / 2.0f, 200.0f}, 20
  );
}

}  // namespace Game