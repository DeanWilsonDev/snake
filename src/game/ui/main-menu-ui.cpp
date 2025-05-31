//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-ui.hpp"

#include "raylib.h"
#include "game-ui.hpp"

namespace Game {

MainMenuUI::MainMenuUI(const Platform::Config::Window::WindowConfig& windowConfig) : GameUI(windowConfig) {}

void MainMenuUI::Render()
{
  DrawTextCentered("Snake", (Vector2){this->windowConfig.width / 2.0f, 40.0f}, 80);
  DrawTextCentered(
      "Press 'Enter' to start", (Vector2){this->windowConfig.width / 2.0f, 200.0f}, 20
  );
}

}  // namespace Game