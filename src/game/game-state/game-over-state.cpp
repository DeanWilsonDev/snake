#include "game-over-state.hpp"
#include "platform/input/i-input.hpp"
#include "gameplay-state-machine.hpp"
#include "game/ui/game-over-ui.hpp"
#include "platform/input/key-codes.hpp"

#include <cassert>

namespace Game {

GameOverState::GameOverState(GameplayStateMachine& stateMachine)
    : gameplayStateMachine(stateMachine)
{
}

void GameOverState::Enter()
{

  this->input = this->gameplayStateMachine.GetInput();
  assert(input);

  const auto gameSettings = this->gameplayStateMachine.GetGameSettings();
  const auto userInterface = this->gameplayStateMachine.GetUserInterface();
  assert(gameSettings);
  assert(userInterface);
  this->gameOverUI =
      new GameOverUI(*userInterface, *gameSettings, this->gameplayStateMachine.GetScore());

  this->gameplayStateMachine.SetGameUI(*this->gameOverUI);
}

void GameOverState::Update(float)
{
  if (this->input->IsKeyPressed(Platform::Input::KeyCode::KEY_ENTER)) {
    this->gameplayStateMachine.Next();
  }
}

void GameOverState::Exit()
{

  if (gameOverUI) {
    delete gameOverUI;
    gameOverUI = nullptr;
  }
  this->gameplayStateMachine.ClearUI();
}

}  // namespace Game
