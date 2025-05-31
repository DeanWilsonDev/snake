#include "game-over-state.hpp"
#include "raylib.h"
#include "../../platform/input/iinput.hpp"
#include "../../platform/input/input-manager.hpp"
#include "gameplay-state-machine.h"

#include <cstdio>

namespace Game {

GameOverState::GameOverState(GameplayStateMachine& stateMachine)
    : gameplayStateMachine(stateMachine)
{
}
void GameOverState::Enter() {}

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

  if (Platform::Input::InputManager::IsKeyPressed(Platform::Input::KeyCode::KEY_ENTER)) {
    this->gameplayStateMachine.Next();
  }
}

void GameOverState::Exit() {}

}  // namespace Game
