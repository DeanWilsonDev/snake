#pragma once

namespace Renderer2D {
class RenderManager;
class IRenderer;
}  // namespace Render2D

class IGameState;
class IUserInterface;
class GameSession;
struct GameSettings;

class IStateMachine {
 public:
  virtual ~IStateMachine() = default;
  virtual void ChangeState(IGameState* newState) = 0;
  virtual void Update(float deltaTime) = 0;
  virtual IGameState* GetCurrentState() = 0;

 protected:
  IGameState* currentState = nullptr;
};
