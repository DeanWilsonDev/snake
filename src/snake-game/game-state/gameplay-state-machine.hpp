#pragma once
#include "engine/state/state-machine.hpp"
#include "core/state/i-game-state.hpp"
#include "engine/input/input-system.hpp"
#include "snake-game/settings/snake-game-settings.hpp"

#include <memory>

namespace Core::Rendering {
class IRenderer;
}

namespace Core::Rendering {
class RenderComponent2DManager;
}  // namespace Core::Rendering

namespace SnakeGame {

struct GameContext {
  int score = {0};
  std::unique_ptr<SnakeGameSettings> settings = {nullptr};
  std::unique_ptr<Engine::Input::InputSystem> input = {nullptr};
};

class GameplayStateMachine final : public Engine::State::StateMachine {
 public:
  explicit GameplayStateMachine(std::unique_ptr<Core::State::IGameState> currentState = nullptr);
  ~GameplayStateMachine() override;
  void Update(float deltaTime) override;
  void DebugUpdate() const override;
  void DebugRender() const override;

  // Setters
  GameContext& GetGameContext() { return this->gameContext; }

 private:
  GameContext gameContext;
};
}  // namespace SnakeGame
