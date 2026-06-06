//
// Created by Dean Wilson on 31/5/2025.
//

#include "game-over-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "core/user-interface/i-user-interface.hpp"
// #include <cstdio>

namespace SnakeGame {

GameOverUI::GameOverUI(int screenWidth, int screenHeight, int& score)
    : screenWidth(screenWidth), screenHeight(screenHeight), score(score)
{
}

void GameOverUI::OnDrawUI(const Core::UserInterface::IUserInterface& ui) const
{
  ui.DrawTextCentered("Game Over", {this->screenWidth / 2.0f - 40, 40}, 80);
  ui.DrawTextCentered("Press 'Enter' to start", {this->screenWidth / 2.0f, 200.0f}, 20);

  // MAIN QUEST: Come back to adding the score after the scoring system has been implemented
  // std::snprintf(this->scoreBuffer, sizeof(this->scoreBuffer), "Score: %d", this->score);
  ui.DrawTextCentered(this->scoreBuffer, {this->screenWidth / 2.0f, 150.0f}, 20);
};

}  // namespace SnakeGame
