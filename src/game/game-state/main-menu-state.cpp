//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-state.hpp"
#include "core/i-game-state.hpp"
#include "game/game-state/gameplay-state.hpp"
#include "gameplay-state-machine.hpp"
#include "umbra/log.h"
#include "platform/input/key-codes.hpp"
#include "game/ui/main-menu-ui.hpp"
#include "platform/input/i-input.hpp"

#include <cassert>
#include <memory>

namespace Game {

MainMenuState::MainMenuState(GameContext& gameContext) : gameContext(gameContext) {}

void MainMenuState::Enter()
{
  this->input = this->gameplayStateMachine->GetInput();
  assert(input);

  const auto gameSettings = this->gameplayStateMachine->GetGameSettings();
  const auto userInterface = this->gameplayStateMachine->GetUserInterface();
  assert(gameSettings);
  assert(userInterface);
  this->mainMenuUI = new MainMenuUI(*userInterface, *gameSettings);

  this->gameplayStateMachine->SetGameUI(*this->mainMenuUI);
}

void MainMenuState::Update(float)
{
  if (!this->input) {
    LOG_ERROR("[MainMenuState] Input is NULL");
    return;
  }

  if (this->input->IsKeyPressed(Platform::Input::KeyCode::KEY_ENTER)) {
    this->gameplayStateMachine->Next();
  }
}

void MainMenuState::Exit()
{
  if (this->mainMenuUI) {
    delete this->mainMenuUI;
    this->mainMenuUI = nullptr;
  }
  this->gameplayStateMachine->ClearUI();
}

std::unique_ptr<Core::IGameState> MainMenuState::GetNextState()
{
  return std::make_unique<GameplayState>(this->gameContext);
}

}  // namespace Game
