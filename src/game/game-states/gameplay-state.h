#pragma once

#include "../../core/igame-state.h"

namespace Renderer2D {
class IRenderer;
}

namespace Game {

class GameplayStateMachine;

class GameplayState : public Core::IGameState {
 public:
  GameplayState(GameplayStateMachine* stateMachine);

  void Enter() override;
  void Update(float deltaTime) override;
  void Exit() override;

 private:
  GameplayStateMachine* stateMachine;
};
}  // namespace Game
