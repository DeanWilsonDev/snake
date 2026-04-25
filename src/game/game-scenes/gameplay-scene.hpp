///
/// Created by Dean Wilson 22 March 2026
///

#pragma once

#include "core/i-game-scene.hpp"
#include "core/rendering/i-renderer.hpp"
#include "game/game-state/gameplay-state-machine.hpp"
#include "core/state/i-game-state.hpp"
#include "core/entity/game-entity-manager.hpp"

namespace Core {

namespace Rendering {
class IRenderer;
}
}  // namespace Core

namespace SnakeGame {
class GameplayStateMachine;

class GameplayScene : public Core::IGameScene {
 public:
  GameplayScene();
  ~GameplayScene();
  void OnEnter(Core::SceneTransitionContext ctx) override;
  void OnExit() override;
  void Update(float deltaTime) override;
  void Render(const Core::Rendering::IRenderer& renderer) override;

 private:
  Core::SceneTransitionContext transition;
  Core::State::IGameState& state;
  Core::GameEntityManager entityManager;
  GameplayStateMachine stateMachine;
};
}  // namespace SnakeGame
