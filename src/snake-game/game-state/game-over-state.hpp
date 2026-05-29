#pragma once

#include "snake-game/game-state/gameplay-state-machine.hpp"
#include "core/state/i-game-state.hpp"
#include <memory>

namespace SnakeGame {

class GameOverUI;

class GameOverState final : public Core::State::IGameState {
 public:
  explicit GameOverState(GameContext& gameContext);
  ~GameOverState() override = default;

  void Enter() override;
  void Update([[maybe_unused]] float deltaTime) override;
  void DebugUpdate() const override;
  void DebugRender() const override;
  void Exit() override;
  virtual std::unique_ptr<Core::State::IGameState> GetNextState() override;

 private:
  GameContext& gameContext;
  GameOverUI* gameOverUI = nullptr;
  char scoreBuffer[100] = {0};
};
}  // namespace SnakeGame
