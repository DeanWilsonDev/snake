//
// Created by Dean Wilson on 31/5/2025.
//

#include "game-over-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "game/settings/game-settings.hpp"
#include "user-interface/i-user-interface.hpp"
#include <cstdio>

namespace Game {

GameOverUI::GameOverUI(UserInterface::IUserInterface& ui, GameSettings& settings, int& score)
    : ui(ui), settings(settings), score(score)
{
}

void GameOverUI::Render()
{
  const auto screenWidth = static_cast<float>(this->settings.GetScreenWidth());

  this->ui.DrawTextCentered("Game Over", {screenWidth / 2.0f - 40, 40}, 80);
  this->ui.DrawTextCentered("Press 'Enter' to start", {screenWidth / 2.0f, 200.0f}, 20);

  std::snprintf(this->scoreBuffer, sizeof(this->scoreBuffer), "Score: %d", this->score);
  this->ui.DrawTextCentered(this->scoreBuffer, {screenWidth / 2.0f, 150.0f}, 20);
}

}  // namespace Game
