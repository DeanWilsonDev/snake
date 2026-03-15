//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-state.hpp"
#include "core/state/i-game-state.hpp"
#include "engine/input/input-action.hpp"
#include "game/game-state/gameplay-state.hpp"
#include "gameplay-state-machine.hpp"

#include <cassert>
#include <memory>

namespace Game {

MainMenuState::MainMenuState(GameContext& gameContext) : gameContext(gameContext) {}

void MainMenuState::Enter()
{

  // const auto gameSettings = this->gameplayStateMachine->GetGameSettings();
  // const auto userInterface = this->gameplayStateMachine->GetUserInterface();
  // assert(gameSettings);
  // assert(userInterface);
  // this->mainMenuUI = new MainMenuUI(*userInterface, *gameSettings);
  //
  // this->gameplayStateMachine->SetGameUI(*this->mainMenuUI);
}

void MainMenuState::Update(float)
{
  if (this->gameContext.input->IsActionPressed(Engine::Input::Action::Confirm)) {
    this->GetNextState();
  }
}

void MainMenuState::DebugUpdate() {}

void MainMenuState::Exit()
{
  // if (this->mainMenuUI) {
  //   delete this->mainMenuUI;
  //   this->mainMenuUI = nullptr;
  // }
  // this->gameplayStateMachine->ClearUI();
}

std::unique_ptr<Core::State::IGameState> MainMenuState::GetNextState()
{
  return std::make_unique<GameplayState>(this->gameContext);
}

}  // namespace Game
