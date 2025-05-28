#include "game-over-state.h"
#include "raylib.h"
#include <cstdio>

void GameOverState::Update(float deltaTime)
{
  LOG_INFO("------------ GAME OVER ---------------");
  // std::ofstream logFile(
  //     "~/development/game-development/cpp/snake-cpp/tmp/debug_log.txt", std::ios::app
  // );
  // if (!logFile.is_open()) {
  //   std::cerr << "Failed to open debug_log.text" << std::endl;
  // }
  // else {
  //   logfile << "Entered STATE_GAME_OVER" << std::endl;
  // }

  if (IsKeyPressed(KEY_ENTER)) {
    // Reinitialize Game State
    stateMachine->changeState(STATE_GAMEPLAY);
  }
}

void GameOverState::Render()
{
  auto& ui = this->stateMachine->getUI();
  auto& settings = this->stateMachine->getSettings();
  auto& session = this->stateMachine->getGameSession();

  ui.drawTextCentered("Game Over", (Vector2){settings.windowWidth / 2.0f - 40, 40}, 80);
  ui.drawTextCentered("Press 'Enter' to start", (Vector2){settings.windowWidth / 2.0f, 200.0f}, 20);
  std::snprintf(this->scoreBuffer, sizeof(this->scoreBuffer), "Score: %d", session.getScore());
  ui.drawTextCentered(this->scoreBuffer, (Vector2){settings.windowWidth / 2.0f, 150.0f}, 20);
}
