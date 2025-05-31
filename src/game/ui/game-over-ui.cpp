//
// Created by Dean Wilson on 31/5/2025.
//

#include "game-over-ui.hpp"

#include "../../platform/window/window-manager.hpp"

namespace Game {

GameOverUI::GameOverUI() {}
void GameOverUI::Render()
{
  DrawTextCentered("Game Over", (Vector2){Platform::Window::WindowManager::GetScreenWidth() / 2.0f - 40, 40}, 80);
  DrawTextCentered("Press 'Enter' to start", (Vector2){Platform::Window::WindowManager::GetScreenWidth() / 2.0f, 200.0f}, 20);
  std::snprintf(this->scoreBuffer, sizeof(this->scoreBuffer), "Score: %d", session.getScore());
  DrawTextCentered(this->scoreBuffer, (Vector2){Platform::Window::WindowManager::GetScreenWidth() / 2.0f, 150.0f}, 20);
}

}  // namespace Game
