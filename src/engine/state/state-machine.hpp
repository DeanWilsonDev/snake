//
// Created by Dean Wilson 28 February 2026
//

#pragma once

#include "core/state/i-state-machine.hpp"
#include "core/state/i-game-state.hpp"
#include <memory>

using namespace Core::State;

namespace Engine {
namespace State {

class StateMachine : public IStateMachine {
 public:
  StateMachine(std::unique_ptr<IGameState> currentState);
  ~StateMachine() = default;
  void ChangeState(std::unique_ptr<IGameState> newState) override;
  virtual void Update(float deltaTime) override;
  virtual void DebugUpdate() const override;
  virtual void DebugRender() const override;
  [[nodiscard]] IGameState& GetCurrentState() override;

 private:
  std::unique_ptr<IGameState> currentState = nullptr;
};

}  // namespace State
}  // namespace Engine
