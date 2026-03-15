#pragma once

#include "core/state/i-game-state.hpp"
#include "game/game-state/gameplay-state-machine.hpp"
#include "game/game-objects/snake.hpp"
#include "game/game-objects/apple.hpp"

#include <memory>

namespace Game {
class GameplayUI;
}
namespace Renderer2D {
class IRenderer;
}

namespace Game {

class GameplayStateMachine;

class GameplayState final : public Core::State::IGameState {
 public:
  explicit GameplayState(GameContext& context);
  ~GameplayState() override = default;

  void Enter() override;
  void Update([[maybe_unused]] float deltaTime) override;
  void DebugUpdate() override;
  void Exit() override;
  std::unique_ptr<Core::State::IGameState> GetNextState() override;

 private:
  GameContext& gameContext;
  GameplayUI* gameplayUI = nullptr;

  std::unique_ptr<Snake> snake = nullptr;
  std::unique_ptr<Apple> apple = nullptr;
};
}  // namespace Game
