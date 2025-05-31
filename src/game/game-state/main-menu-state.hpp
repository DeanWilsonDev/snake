#pragma once
#include "../../core/igame-state.h"

//
// Created by Dean Wilson on 30/5/2025.
//

namespace Game {

class GameplayStateMachine;
class MainMenuUI;

class MainMenuState final : public Core::IGameState {
 public:
  explicit MainMenuState(GameplayStateMachine& gameplayStateMachine);
  void Enter() override;
  void Update(float deltaTime) override;
  void Exit() override;

 private:
  GameplayStateMachine& gameplayStateMachine;
  MainMenuUI* mainMenuUI;
};

}  // namespace Game
