//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu.h"

#include "raylib.h"

namespace Game::UI{

MainMenu::MainMenu() {}

void MainMenu::Render()
{
  this->DrawTextCentered("Snake", (Vector2){settings.windowWidth / 2.0f, 40.0f}, 80);
  ui->drawTextCentered(
      "Press 'Enter' to start", (Vector2){settings.windowWidth / 2.0f, 200.0f}, 20
  );
  if (IsKeyPressed(KEY_ENTER)) {
    this->session->setState(STATE_GAMEPLAY);
  }

}

}