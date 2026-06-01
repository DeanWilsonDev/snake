//
// Created by Dean Wilson on 31/5/2025.
//

#include "game-over-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "user-interface/i-user-interface.hpp"
#include <cstdio>

namespace SnakeGame {

GameOverUI::GameOverUI(
    UserInterface::IUserInterface& ui, int screenWidth, int screenHeight, int& score
)
    : ui(ui), screenWidth(screenWidth), screenHeight(screenHeight), score(score)
{
}

void GameOverUI::OnDrawUI()
{
  this->ui.DrawTextCentered("Game Over", {this->screenWidth / 2.0f - 40, 40}, 80);
  this->ui.DrawTextCentered("Press 'Enter' to start", {this->screenWidth / 2.0f, 200.0f}, 20);

  std::snprintf(this->scoreBuffer, sizeof(this->scoreBuffer), "Score: %d", this->score);
  this->ui.DrawTextCentered(this->scoreBuffer, {this->screenWidth / 2.0f, 150.0f}, 20);
};

}  // namespace SnakeGame
