

#include "game-over-state.h"

void GameOverState::update(float deltaTime)
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
    context->changeState(STATE_GAMEPLAY);
  }
}

void GameOverState::render()
{
  auto& ui = this->context->getUI();
  auto& settings = this->context->getSettings();
  auto& session = this->context->getGameSession();

  ui.drawTextCentered("Game Over", (Vector2){settings.windowWidth / 2.0f - 40, 40}, 80);
  ui.drawTextCentered("Press 'Enter' to start", (Vector2){settings.windowWidth / 2.0f, 200.0f}, 20);
  std::snprintf(this->scoreBuffer, sizeof(this->scoreBuffer), "Score: %d", session.getScore());
  ui.drawTextCentered(this->scoreBuffer, (Vector2){settings.windowWidth / 2.0f, 150.0f}, 20);
}
