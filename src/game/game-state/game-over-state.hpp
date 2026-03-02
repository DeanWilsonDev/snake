#pragma once

#include "game/game-state/gameplay-state-machine.hpp"
#include "core/i-game-state.hpp"
#include <memory>

namespace Game {

class GameOverUI;

class GameOverState final : public Core::IGameState {
 public:
  explicit GameOverState(GameContext& gameContext);
  ~GameOverState() override = default;

  void Enter() override;
  void Update([[maybe_unused]] float deltaTime) override;
  void DebugUpdate() override;
  void Exit() override;
  std::unique_ptr<Core::IGameState> GetNextState() override;

 private:
  GameContext& gameContext;
  GameOverUI* gameOverUI = nullptr;
  char scoreBuffer[100] = {0};
};
}  // namespace Game
