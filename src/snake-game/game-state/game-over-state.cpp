#include "game-over-state.hpp"
#include "engine/input/input-action.hpp"
#include "snake-game/game-state/gameplay-state.hpp"
#include "gameplay-state-machine.hpp"
#include "core/state/i-game-state.hpp"

#include <cassert>
#include <memory>

namespace SnakeGame {

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
  if (this->gameContext.input->IsActionPressed(Engine::Input::Action::Confirm)) {
    this->GetNextState();
  }
}

void GameOverState::DebugUpdate() const {}
void GameOverState::DebugRender() const {}

void GameOverState::Exit()
{
  // if (gameOverUI) {
  //   delete gameOverUI;
  //   gameOverUI = nullptr;
  // }
  // this->gameplayStateMachine.ClearUI();
}

std::unique_ptr<Core::State::IGameState> GameOverState::GetNextState()
{
  return std::make_unique<GameplayState>(this->gameContext);
}

}  // namespace SnakeGame
