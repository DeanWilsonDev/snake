//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once

#include <memory>
#include "core/state/i-game-state.hpp"
#include "gameplay-state-machine.hpp"

namespace SnakeGame {

class MainMenuUI;

class MainMenuState final : public Core::State::IGameState {
 public:
  explicit MainMenuState(GameContext& context);
  ~MainMenuState() override = default;

  void Enter() override;
  void Update([[maybe_unused]] float deltaTime) override;
  void DebugUpdate() const override;
  void DebugRender() const override;
  void Exit() override;
  std::unique_ptr<Core::State::IGameState> GetNextState() override;

 private:
  GameContext& gameContext;
  MainMenuUI* mainMenuUI = nullptr;
};

}  // namespace SnakeGame
