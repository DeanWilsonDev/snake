#include "game-over-state.hpp"
#include "game/game-state/gameplay-state.hpp"
#include "platform/input/i-input.hpp"
#include "gameplay-state-machine.hpp"
#include "game/ui/game-over-ui.hpp"
#include "platform/input/key-codes.hpp"

#include <cassert>
#include <memory>

namespace Game {

GameOverState::GameOverState(GameContext& gameContext) : gameContext(gameContext) {}

void GameOverState::Enter()
{
  // MAIN QUEST: [GameOverState] Fix Input
  // this->input = this->gameplayStateMachine.GetInput();
  // assert(input);

  // MAIN QUEST: [GameOverState] Fix UI
  // const auto gameSettings = this->gameplayStateMachine.GetGameSettings();
  // const auto userInterface = this->gameplayStateMachine.GetUserInterface();
  // assert(gameSettings);
  // assert(userInterface);
  // this->gameOverUI =
  //     new GameOverUI(*userInterface, *gameSettings, this->gameplayStateMachine.GetScore());
  // this->gameplayStateMachine.SetGameUI(*this->gameOverUI);
}

void GameOverState::Update(float)
{
  if (this->input->IsKeyPressed(Platform::Input::KeyCode::KEY_ENTER)) {
    this->GetNextState();
  }
}

void GameOverState::Exit()
{
  // if (gameOverUI) {
  //   delete gameOverUI;
  //   gameOverUI = nullptr;
  // }
  // this->gameplayStateMachine.ClearUI();
}

std::unique_ptr<Core::IGameState> GameOverState::GetNextState()
{
  return std::make_unique<GameplayState>(this->gameContext);
}

}  // namespace Game
