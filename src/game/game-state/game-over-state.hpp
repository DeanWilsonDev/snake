#pragma once

#include "core/i-game-state.h"

namespace Platform::Input {
class IInput;
}
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
  Platform::Input::IInput* input = nullptr;
  char scoreBuffer[100] = {0};
};
}  // namespace Game
