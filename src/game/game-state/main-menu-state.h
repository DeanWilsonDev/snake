#pragma once
#include "../../core/igame-state.h"

//
// Created by Dean Wilson on 30/5/2025.
//

namespace Game::UI {
class MainMenu;
}

namespace Game {
class GameplayStateMachine;
}
namespace Game {

class MainMenuState final : public Core::IGameState {
 public:
  explicit MainMenuState(GameplayStateMachine& gameplayStateMachine);
  void Enter() override;
  void Update(float deltaTime) override;
  void Exit() override;

 private:
  GameplayStateMachine& gameplayStateMachine;
  UI::MainMenu* mainMenuUI;
};

}  // namespace Game
