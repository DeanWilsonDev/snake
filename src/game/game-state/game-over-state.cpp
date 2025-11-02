#include "game-over-state.hpp"
#include "platform/input/i-input.hpp"
#include "gameplay-state-machine.hpp"
#include "game/ui/game-over-ui.hpp"
#include <umbra/log.h>

#include <cassert>

namespace Game {

GameOverState::GameOverState(GameplayStateMachine& stateMachine)
    : gameplayStateMachine(stateMachine)
{
}

void GameOverState::Enter()
{
  LOG_TRACE("[GameOverState] Entering State");

  LOG_TRACE("[GameOverState] Setting up Input");
  this->input = this->gameplayStateMachine.GetInput();
  assert(input);

  LOG_TRACE("[GameOverState] Initializing Main Menu UI");
  const auto gameSettings = this->gameplayStateMachine.GetGameSettings();
  const auto userInterface = this->gameplayStateMachine.GetUserInterface();
  LOG_TRACE("[GameOverState] Validating Game Settings");
  assert(gameSettings);
  LOG_TRACE("[GameOverState] Validating User Interface");
  assert(userInterface);
  LOG_TRACE("[GameOverState] Setting Game Over UI");
  this->gameOverUI =
      new GameOverUI(*userInterface, *gameSettings, this->gameplayStateMachine.GetScore());

  LOG_TRACE("[GameOverState] Setting Game Over UI as Active Game UI");
  this->gameplayStateMachine.SetGameUI(*this->gameOverUI);
  LOG_INFO("------------ GAME OVER ---------------");
}

void GameOverState::Update(float deltaTime)
{
  if (this->input->IsKeyPressed(Platform::Input::KeyCode::KEY_ENTER)) {
    this->gameplayStateMachine.Next();
  }
}

void GameOverState::Exit()
{
  LOG_TRACE("[GameOverState] Exiting State");

  if (gameOverUI) {
    delete gameOverUI;
    gameOverUI = nullptr;
  }
  this->gameplayStateMachine.ClearUI();
}

}  // namespace Game
