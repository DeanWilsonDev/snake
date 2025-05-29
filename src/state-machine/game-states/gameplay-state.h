#pragma once

#include "igame-state.h"
#include "../../core/irenderable.h"

class GameSession;
struct GameSettings;
class GameplayStateMachine;

class GameplayState : public IGameState, IRenderable {
 public:
  GameplayState(GameplayStateMachine* stateMachine, GameSettings& settings);

  void Enter() override;
  void Update(float deltaTime) override;
  void Draw(IRenderer* renderer);
  void Exit() override;

 private:
  GameplayStateMachine* stateMachine;
  GameSettings& settings;
};