#pragma once

#include <memory>
#include "core/debug/i-debugable.hpp"
#include "core/i-updatable.hpp"
namespace Core {
namespace State {

class IGameState : public IUpdatable, Debug::IDebugable {
 public:
  virtual ~IGameState() = default;
  virtual void Enter() = 0;
  virtual void Update([[maybe_unused]] float deltaTime) override = 0;
  virtual void DebugUpdate() const override = 0;
  virtual void DebugRender() const override = 0;
  virtual void Exit() = 0;
  virtual std::unique_ptr<IGameState> GetNextState() = 0;
};
}  // namespace State
}  // namespace Core
