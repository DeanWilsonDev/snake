#pragma once

namespace Core {

class IGameState;

class IStateMachine {
 public:
  virtual ~IStateMachine() = default;
  virtual void ChangeState(IGameState* newState) = 0;
  virtual void Update(float deltaTime) = 0;
  virtual IGameState* GetCurrentState() = 0;

 protected:
  IGameState* currentState = nullptr;
};
}  // namespace Core
