#include "game-over-state.hpp"
#include "platform/input/i-input.hpp"
#include "gameplay-state-machine.hpp"
#include "log.h"

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
}

}  // namespace Game
