#pragma once

#include <memory>
#include "core/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include "core/i-game-state.hpp"

namespace Core {

class IGameState;

class IStateMachine : public IUpdatable, IDebugable {
 public:
  virtual ~IStateMachine() = default;
  virtual void ChangeState(std::unique_ptr<IGameState> newState) = 0;
  virtual void Update(float deltaTime) = 0;
  virtual void DebugUpdate() = 0;
  [[nodiscard]] virtual IGameState& GetCurrentState() = 0;
  virtual void Next() = 0;
};
}  // namespace Core
