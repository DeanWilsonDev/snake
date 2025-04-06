#pragma once

#include "igame-context.h"
#include "igame-state.h"
#include "game-settings.h"
#include "game-session.h"
#include "raylib-ui.h"

class Game : IGameContext {
 public:
  void update(float deltaTime) { currentState->update(deltaTime); }
  void render() { currentState->render(); }

  void changeState(IGameState* newState) override
  {
    delete currentState;
    currentState = newState;
  };

  GameSettings& getSettings() override { return settings; }

  GameSession& getGameSession() override { return state; }

  IUserInterface& getUI() override { return ui; }

 private:
  GameSession state;
  GameSettings settings;
  IGameState* currentState = nullptr;
  RaylibUI ui;
};
