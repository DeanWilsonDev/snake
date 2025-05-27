#pragma once
#include "istate-machine.h"

class IGameState;
struct GameSettings;
class GameSession;
class IUserInterface;
class RaylibUI;

class GameplayStateMachine : public IStateMachine {
public:
  GameplayStateMachine();
  ~GameplayStateMachine() override;
  void changeState(IGameState* newState) override;
  GameSettings& getSettings() override;
  GameSession& getGameSession() override;
  IUserInterface& getUI() override;

private:
  GameSession* session;
  GameSettings& settings;
  IGameState* currentState = nullptr;
  RaylibUI& ui;
};
