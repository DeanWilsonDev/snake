//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-state.h"
#include "../ui/main-menu.h"
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
    this->gameplayStateMachine.ChangeState(State::STATE_GAMEPLAY);
  }
}

void MainMenuState::Exit()
{
  this->gameplayStateMachine.ClearUI();
  delete this->mainMenuUI;
}

}  // namespace Game