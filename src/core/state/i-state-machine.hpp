#pragma once

#include <memory>
#include "core/debug/i-debugable.hpp"
#include "core/i-updatable.hpp"

namespace Core {
namespace State {

class IGameState;

class IStateMachine : public IUpdatable, Debug::IDebugable {
 public:
  virtual ~IStateMachine() = default;
  virtual void ChangeState(std::unique_ptr<IGameState> newState) = 0;
  virtual void Update(float deltaTime) = 0;
  virtual void DebugUpdate() const = 0;
  virtual void DebugRender() const = 0;
  [[nodiscard]] virtual IGameState& GetCurrentState() = 0;
};
}  // namespace State
}  // namespace Core
