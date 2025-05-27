#pragma once

#include "state-machine/istate-machine.h"
#include "game-states/igame-state.h"
#include "game-settings.h"
#include "game-session.h"
#include "raylib-ui.h"

class Game : IStateMachine {
 public:
  Game();
  void update(float deltaTime) { currentState->update(deltaTime); }
  void render() { currentState->render(); }

  void changeState(IGameState* newState) override
  {
    delete currentState;
    currentState = newState;
  };

  GameSettings& getSettings() override { return settings; }

  GameSession& getGameSession() override { return session; }

  IUserInterface& getUI() override { return ui; }

 private:
  GameSession session;
  GameSettings settings;
  IGameState* currentState = nullptr;
  RaylibUI ui;
};
