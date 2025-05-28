#pragma once

#include "igame-state.h"

class IUserInterface;
class IStateMachine;
class GameplayStateMachine;

class GameOverState : public IGameState {
 public:
  GameOverState(GameplayStateMachine* stateMachine) : stateMachine(stateMachine) {}

  void Update(float deltaTime) override;
  void Render() override;

 private:
  GameplayStateMachine* stateMachine;
  char scoreBuffer[100] = {0};
};
