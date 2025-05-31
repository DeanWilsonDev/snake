#pragma once

#include "../../core/igame-state.h"

namespace Renderer2D {
class IRenderer;
}

namespace Game {

class GameplayStateMachine;

class GameplayState final : public Core::IGameState {
 public:
  explicit GameplayState(GameplayStateMachine* stateMachine);

  void Enter() override;
  void Update(float deltaTime) override;
  void Exit() override;

 private:
  GameplayStateMachine* gameplayStateMachine;
};
}  // namespace Game
