#pragma once

#include "igame-state.h"

class IUserInterface;
class IStateMachine;

class GameOverState : public IGameState {
 public:
  GameOverState(IStateMachine* context) : context(context) {}

  void update(float deltaTime) override;
  void render() override;

 private:
  IStateMachine* context;
  IUserInterface* ui;
  char scoreBuffer[100] = {0};
};
