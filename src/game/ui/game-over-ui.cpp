//
// Created by Dean Wilson on 31/5/2025.
//

#include "game-over-ui.hpp"

namespace Game {

GameOverUI::GameOverUI(const Platform::Config::Window::WindowConfig& windowConfig): GameUI(windowConfig) {}
void GameOverUI::Render()
{
  DrawTextCentered("Game Over", (Vector2){this->windowConfig.width / 2.0f - 40, 40}, 80);
  DrawTextCentered("Press 'Enter' to start", (Vector2){this->windowConfig.width / 2.0f, 200.0f}, 20);
  std::snprintf(this->scoreBuffer, sizeof(this->scoreBuffer), "Score: %d", session.getScore());
  DrawTextCentered(this->scoreBuffer, (Vector2){settings.windowWidth / 2.0f, 150.0f}, 20);
}

}  // namespace Game
