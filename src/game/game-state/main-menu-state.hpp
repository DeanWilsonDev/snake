#pragma once
#include "core/i-game-state.h"

//
// Created by Dean Wilson on 30/5/2025.
//

namespace Platform::Input {
class IInput;
}
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
  MainMenuUI* mainMenuUI = nullptr;
  Platform::Input::IInput* input = nullptr;
};

}  // namespace Game
