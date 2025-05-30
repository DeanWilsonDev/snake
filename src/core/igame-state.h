#pragma once

namespace Core {

class IGameState {
 public:
  virtual ~IGameState() = default;
  virtual void Enter() = 0;
  virtual void Update(float deltaTime) = 0;
  virtual void Exit() = 0;
};
}  // namespace Core
