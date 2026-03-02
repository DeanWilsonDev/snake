
#include "state-machine.hpp"
#include "core/i-game-state.hpp"

#include <umbra/log.h>

#include <memory>
#include <utility>

namespace Core {

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

void StateMachine::DebugUpdate() {}

IGameState& StateMachine::GetCurrentState()
{
  return *this->currentState;
}

}  // namespace Core
