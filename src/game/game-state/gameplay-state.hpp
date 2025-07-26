#pragma once

#include "core/i-game-state.h"

namespace Platform::Input {
class IInput;
}
namespace Game {
class GameplayUI;
}
namespace Renderer2D {
class IRenderer;
}

namespace Game {

class GameplayStateMachine;

class GameplayState final : public Core::IGameState {
 public:
  explicit GameplayState(GameplayStateMachine& stateMachine);

  void Enter() override;
  void Update(float deltaTime) override;
  void Exit() override;

 private:
  GameplayStateMachine& gameplayStateMachine;
  GameplayUI* gameplayUI = nullptr;
  Platform::Input::IInput* input = nullptr;
};
}  // namespace Game
