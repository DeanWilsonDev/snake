#pragma once

#include "core/i-game-state.hpp"
#include "game/game-state/gameplay-state-machine.hpp"
#include <memory>

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
  explicit GameplayState(GameContext& context);

  void Enter() override;
  void Update([[maybe_unused]] float deltaTime) override;
  void DebugUpdate() override;
  void Exit() override;
  std::unique_ptr<Core::IGameState> GetNextState() override;

 private:
  GameContext& gameContext;
  GameplayUI* gameplayUI = nullptr;
  Platform::Input::IInput* input = nullptr;

  std::unique_ptr<Snake> snake = nullptr;
  std::unique_ptr<Apple> apple = nullptr;
};
}  // namespace Game
