#pragma once
#include "istate-machine.h"

class Apple;
class Snake;
class IGameState;
struct GameSettings;
class GameSession;
class IUserInterface;
class RaylibUI;

class GameplayStateMachine final : public IStateMachine {
 public:
  GameplayStateMachine(
      IGameState* currentState, GameSettings settings, IUserInterface* ui, Snake* snake,
      Apple* apple
  );
  ~GameplayStateMachine() override;
  void ChangeState(IGameState* newState) override;
  IGameState* GetState() override;
  GameSettings& GetSettings() override;
  GameSession& GetGameSession() override;
  IUserInterface* GetUI() override;

  [[nodiscard]] IGameState* GetCurrentState() const { return this->currentState; };
  [[nodiscard]] int GetScore() const { return this->score; };
  void IncreaseScore();

 private:
  GameSettings& settings;
  IGameState* currentState = nullptr;
  IUserInterface* ui;
  Snake* snake;
  Apple* apple;
  int score;
};
