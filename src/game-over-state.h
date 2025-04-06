#pragma once

#include "igame-state.h"
#include "igame-context.h"
#include "iuser-interface.h"

class GameOverState : public IGameState {
 public:
  GameOverState(IGameContext* context) : context(context) {}

  void update(float deltaTime) override;
  void render() override;

 private:
  IGameContext* context;
  IUserInterface* ui;
  char scoreBuffer[100] = {0};
};
