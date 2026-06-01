
#include "state-machine.hpp"
#include "core/state/i-game-state.hpp"

#include <memory>
#include <utility>

namespace Core::State {

StateMachine::StateMachine(std::unique_ptr<IGameState> currentState)
    : currentState(std::move(currentState))
{
}

void StateMachine::ChangeState(std::unique_ptr<IGameState> newState)
{
  if (this->currentState) {
    this->currentState->Exit();
  }

  this->currentState = std::move(newState);

  if (this->currentState) {
    this->currentState->Enter();
  }
}

void StateMachine::Update(float deltaTime)
{
  if (!this->currentState) {
    return;
  }
  this->currentState->Update(deltaTime);
};


IGameState& StateMachine::GetCurrentState()
{
  return *this->currentState;
}

}  // namespace Core::State
