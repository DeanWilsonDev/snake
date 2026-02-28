//
// Created by Dean Wilson on 26/7/2025.
//

#include "gameplay-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "game/settings/game-settings.hpp"
#include "user-interface/i-user-interface.hpp"

#include <cstdio>

namespace Game {
GameplayUI::GameplayUI(UserInterface::IUserInterface& ui, GameSettings& settings, int& score)
    : ui(ui), settings(settings), score(score)
{
}

void GameplayUI::Render()
{
  const auto textPosition = Core::Math::Vector2D{80.f, 30.f};
  constexpr int fontSize = 20;
  std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", this->score);
  this->ui.DrawTextCentered(scoreBuffer, textPosition, fontSize);
}

}  // namespace Game
