//
// Created by Dean Wilson 28 February 2026
//

#pragma once

#include "core/i-state-machine.hpp"
#include "core/i-game-state.hpp"
#include <memory>

namespace Core {

class StateMachine : public IStateMachine {
 public:
  StateMachine(std::unique_ptr<IGameState> currentState);
  ~StateMachine() = default;
  virtual void Update(float deltaTime) override;
  virtual void DebugUpdate() override;
  virtual void Next() override;
  void ChangeState(std::unique_ptr<IGameState> newState) override;
  [[nodiscard]] IGameState& GetCurrentState() override;
 private:
  std::unique_ptr<IGameState> currentState = nullptr;
};

}  // namespace Core
