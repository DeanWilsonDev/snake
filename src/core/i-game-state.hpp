#pragma once

#include <memory>
#include "core/i-debugable.hpp"
#include "core/i-updatable.hpp"
namespace Core {

class IGameState : public IUpdatable, IDebugable {
 public:
  virtual ~IGameState() = default;
  virtual void Enter() = 0;
  virtual void Update([[maybe_unused]] float deltaTime) override;
  virtual void DebugUpdate() override {};
  virtual void Exit() = 0;
  virtual std::unique_ptr<IGameState> GetNextState() = 0;
};
}  // namespace Core
