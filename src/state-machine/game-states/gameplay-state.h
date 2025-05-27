#pragma once

#include "igame-state.h"

class IUserInterface;
class IStateMachine;
class GameplayState : public IGameState {
public:
  GameplayState(IStateMachine* context) : context(context){}

  void update(float deltaTime) override;
  void render() override;


private:
  IStateMachine* context;
  IUserInterface* ui;
};