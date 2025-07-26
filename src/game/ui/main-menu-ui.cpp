//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "game/settings/game-settings.h"
#include "user-interface/i-user-interface.hpp"

namespace Game {

MainMenuUI::MainMenuUI(UserInterface::IUserInterface& ui, GameSettings& settings)
    : settings(settings), ui(ui)
{
}

void MainMenuUI::Render()
{
  const auto screenWidth = static_cast<float>(this->settings.GetScreenWidth());

  this->ui.DrawTextCentered("Snake", (Core::Math::Vector2D){screenWidth / 2.0f, 40.0f}, 80);
  this->ui.DrawTextCentered(
      "Press 'Enter' to start", (Core::Math::Vector2D){screenWidth / 2.0f, 200.0f}, 20
  );
}

}  // namespace Game