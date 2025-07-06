#include "game-over-state.hpp"
#include "platform/input/iinput.hpp"
#include "platform/input/input-manager.hpp"
#include "gameplay-state-machine.hpp"
#include "log.h"

namespace Game {

GameOverState::GameOverState(GameplayStateMachine& stateMachine)
    : gameplayStateMachine(stateMachine)
{
}
void GameOverState::Enter() {}

void GameOverState::Update(float deltaTime)
{
  LOG_INFO("------------ GAME OVER ---------------");

  if (Platform::Input::InputManager::IsKeyPressed(Platform::Input::KeyCode::KEY_ENTER)) {
    this->gameplayStateMachine.Next();
  }
}

void GameOverState::Exit() {}

}  // namespace Game
