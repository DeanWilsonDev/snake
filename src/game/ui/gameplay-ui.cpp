//
// Created by Dean Wilson on 26/7/2025.
//

#include "gameplay-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "game/game-state/gameplay-state-machine.hpp"
#include "user-interface/i-user-interface.hpp"

#include <cstdio>

namespace Game {
GameplayUI::GameplayUI(GameContext& gameContext): gameContext(gameContext)
{
}

void GameplayUI::Render()
{
  const auto textPosition = Core::Math::Vector2D{80.f, 30.f};
  constexpr int fontSize = 20;
  std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", this->gameContext.score);
  // MAIN QUEST: Change how this works so that the GameUI can simply layout the UI how it wants and have the engine handle everything else
  // this->ui.DrawTextCentered(scoreBuffer, textPosition, fontSize);
}

}  // namespace Game
