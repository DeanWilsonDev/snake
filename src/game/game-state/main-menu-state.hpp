//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once

#include <memory>
#include "core/i-game-state.hpp"
#include "gameplay-state-machine.hpp"

namespace Platform::Input {
class IInput;
}
namespace Game {

class GameplayStateMachine;
class MainMenuUI;

class MainMenuState final : public Core::IGameState {
 public:
  explicit MainMenuState(GameContext& context);
  ~MainMenuState() override = default;
  void Enter() override;
  void Update([[maybe_unused]] float deltaTime) override;
  void Exit() override;
  std::unique_ptr<Core::IGameState> GetNextState() override;

 private:
  GameContext& gameContext;
  MainMenuUI* mainMenuUI = nullptr;
  Platform::Input::IInput* input = nullptr;
};

}  // namespace Game
