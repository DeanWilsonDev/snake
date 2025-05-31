#pragma once

#include "../../core/igame-state.h"

class IUserInterface;
class IStateMachine;

namespace Game {
class GameplayStateMachine;

class GameOverState final : public Core::IGameState {
 public:
  explicit GameOverState(GameplayStateMachine& stateMachine);

  void Enter() override;
  void Update(float deltaTime) override;
  void Exit() override;

 private:
  GameplayStateMachine& gameplayStateMachine;
  char scoreBuffer[100] = {0};
};
}  // namespace Game
