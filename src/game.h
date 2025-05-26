#pragma once

#include "igame-context.h"
#include "igame-state.h"
#include "game-settings.h"
#include "game-session.h"
#include "raylib-ui.h"

class Game : IGameContext {
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
