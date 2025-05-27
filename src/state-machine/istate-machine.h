#pragma once

class IGameState;
class IUserInterface;
class GameSession;
struct GameSettings;

class IStateMachine {
 public:
  virtual ~IStateMachine() = default;
  virtual void changeState(IGameState* newState) = 0;
  virtual GameSettings& getSettings() = 0;
  virtual GameSession& getGameSession() = 0;
  virtual IUserInterface& getUI() = 0;
};
