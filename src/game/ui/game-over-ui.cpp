//
// Created by Dean Wilson on 31/5/2025.
//

#include "game-over-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "platform/window/window-manager.hpp"
#include "user-interface/user-interface-manager.hpp"

#include <cstdio>

// Main Quest: [GameOverUI] update Game Over UI class

namespace Game {

GameOverUI::GameOverUI(const int score): score(score)
{

}

void GameOverUI::Render()
{
  const auto screenWidth = static_cast<float>(Platform::Window::WindowManager::GetScreenWidth());

  UserInterface::UserInterfaceManager::DrawTextCentered("Game Over", Core::Math::Vector2D{screenWidth / 2.0f - 40, 40}, 80);
  UserInterface::UserInterfaceManager::DrawTextCentered("Press 'Enter' to start", Core::Math::Vector2D{screenWidth / 2.0f, 200.0f}, 20);

  std::snprintf(this->scoreBuffer, sizeof(this->scoreBuffer), "Score: %d", session.getScore());

  UserInterface::UserInterfaceManager::DrawTextCentered(this->scoreBuffer, Core::Math::Vector2D{screenWidth / 2.0f, 150.0f}, 20);
}

}  // namespace Game
