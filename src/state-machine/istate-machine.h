#pragma once

class IGameState;
class IUserInterface;
class GameSession;
struct GameSettings;

class IStateMachine {
 public:
  virtual ~IStateMachine() = default;
  virtual void ChangeState(IGameState* newState) = 0;
  virtual IGameState* GetState() = 0;
  virtual GameSettings& GetSettings() = 0;
  virtual GameSession& GetGameSession() = 0;
  virtual IUserInterface* GetUI() = 0;
protected:
  IGameState* currentState = nullptr;
};
