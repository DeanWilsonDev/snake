#pragma once

#include "../../core/igame-state.h"

class IUserInterface;
class IStateMachine;
class GameplayStateMachine;

namespace Game {

class GameOverState : public Core::IGameState {
 public:
  GameOverState(GameplayStateMachine* stateMachine) : stateMachine(stateMachine) {}

  void Enter() override;
  void Update(float deltaTime) override;
  void Exit() override;

 private:
  GameplayStateMachine* stateMachine;
  char scoreBuffer[100] = {0};
};
}  // namespace Game
