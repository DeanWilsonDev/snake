//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu.h"

#include "raylib.h"
#include "game-ui.h"

namespace Game::UI{

MainMenu::MainMenu() : GameUI()
{

}

void MainMenu::Render()
{

  DrawTextCentered("Snake", (Vector2){this->windowConfig.width / 2.0f, 40.0f}, 80);
  DrawTextCentered(
      "Press 'Enter' to start", (Vector2){this->windowConfig.width / 2.0f, 200.0f}, 20
  );

  if (IsKeyPressed(KEY_ENTER)) {
    this->session->setState(STATE_GAMEPLAY);
  }

}

}