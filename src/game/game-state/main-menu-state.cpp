//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-state.hpp"
#include "gameplay-state-machine.hpp"
#include "game/settings/game-settings.h"
#include "game/ui/main-menu-ui.hpp"
#include "platform/input/i-input.hpp"

#include <cassert>

namespace Game {

MainMenuState::MainMenuState(GameplayStateMachine& gameplayStateMachine)
    : gameplayStateMachine(&gameplayStateMachine)
{
}

void MainMenuState::Enter()
{
  LOG_TRACE("[MainMenuState] Entering State");

  LOG_TRACE("[MainMenuState] Setting up Input");
  this->input = this->gameplayStateMachine->GetInput();
  assert(input);

  LOG_TRACE("[MainMenuState] Initializing Main Menu UI");
  const auto gameSettings = this->gameplayStateMachine->GetGameSettings();
  const auto userInterface = this->gameplayStateMachine->GetUserInterface();
  LOG_TRACE("[MainMenuState] Validating Game Settings");
  assert(gameSettings);
  LOG_TRACE("[MainMenuState] Validating User Interface");
  assert(userInterface);
  LOG_TRACE("[MainMenuState] Setting Main Menu UI");
  this->mainMenuUI = new MainMenuUI(*userInterface, *gameSettings);

  LOG_TRACE("[MainMenuState] Setting Main Menu UI as Active Game UI");
  this->gameplayStateMachine->SetGameUI(*this->mainMenuUI);
}

void MainMenuState::Update(float deltaTime)
{

  if (!this->input) {
    LOG_ERROR("[MainMenuState] Input is NULL");
    return;
  }

  if (this->input->IsKeyPressed(Platform::Input::KeyCode::KEY_ENTER)) {
    LOG_TRACE("[MainMenuState] Changing to next state");
    this->gameplayStateMachine->Next();
  }
}

void MainMenuState::Exit()
{
  LOG_TRACE("[MainMenuState] Exiting State");

  if (this->mainMenuUI) {
    delete this->mainMenuUI;
    this->mainMenuUI = nullptr;
  }
  this->gameplayStateMachine->ClearUI();
}

}  // namespace Game