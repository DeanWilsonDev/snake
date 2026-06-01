//
// Created by Dean Wilson 28 February 2026
//

#pragma once

#include "core/state/i-state-machine.hpp"
#include "core/state/i-game-state.hpp"
#include <memory>

namespace Core {

namespace State {

class StateMachine : public IStateMachine {
 public:
  StateMachine(std::unique_ptr<IGameState> currentState);
  ~StateMachine() = default;
  virtual void Update(float deltaTime) override;
  void ChangeState(std::unique_ptr<IGameState> newState) override;
  [[nodiscard]] IGameState& GetCurrentState() override;

 private:
  std::unique_ptr<IGameState> currentState = nullptr;
};

}  // namespace State
}  // namespace Core
