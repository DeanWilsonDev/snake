#pragma once

class IGameState {
 public:
  virtual ~IGameState() = default;
  virtual void update(float deltaTime) = 0;
  virtual void render() = 0;
};
