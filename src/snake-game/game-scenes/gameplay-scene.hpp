///
/// Created by Dean Wilson 22 March 2026
///

#pragma once

#include <memory>
#include "core/i-game-scene.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/rendering/render-component-2d-manager.hpp"
#include "snake-game/game-state/gameplay-state-machine.hpp"
#include "core/entity/game-entity-manager.hpp"
#include "core/events/i-event-bus.hpp"

namespace Core {

namespace Rendering {
class IRenderer;
}
}  // namespace Core

namespace SnakeGame {
class GameplayStateMachine;

struct GameplaySceneParams {
  std::shared_ptr<Core::Events::IEventBus> eventBus;
};

class GameplayScene : public Core::IGameScene {
 public:
  GameplayScene(const GameplaySceneParams& params);
  ~GameplayScene();
  void Initialize() override;
  void OnEnter(Core::SceneTransitionContext ctx) override;
  void OnExit() override;
  void Update(float deltaTime) override;
  void OnRender(const Core::Rendering::IRenderer& renderer) const override;
  void DebugUpdate() override;
  void DebugRender() override;

 private:
  Core::SceneTransitionContext transition;
  Core::GameEntityManager entityManager;
  Core::Rendering::RenderComponent2DManager renderComponentManager;
  GameplayStateMachine stateMachine;
  std::shared_ptr<Core::Events::IEventBus> eventBus;
};
}  // namespace SnakeGame
