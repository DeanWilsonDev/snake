//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-state.hpp"
#include "../ui/main-menu-ui.hpp"
#include "gameplay-state-machine.h"
#include "../../platform/input/input-manager.hpp"

namespace Game {

MainMenuState::MainMenuState(GameplayStateMachine& gameplayStateMachine)
    : gameplayStateMachine(gameplayStateMachine)
{
}

void MainMenuState::Enter()
{
  this->mainMenuUI = new UI::MainMenu();
  this->gameplayStateMachine.SetUI(*mainMenuUI);
}

void MainMenuState::Update(float deltaTime)
{
  if (Platform::Input::InputManager::IsKeyPressed(Platform::Input::KeyCode::KEY_ENTER)) {
    this->gameplayStateMachine.Next();
  }
}

void MainMenuState::Exit()
{
  this->gameplayStateMachine.ClearUI();
  delete this->mainMenuUI;
}

}  // namespace Game