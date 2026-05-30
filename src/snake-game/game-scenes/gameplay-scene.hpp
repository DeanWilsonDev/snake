///
/// Created by Dean Wilson 22 March 2026
///

#pragma once

#include "core/scenes/i-game-scene.hpp"
#include "core/rendering/i-renderer.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "snake-game/game-state/gameplay-state-machine.hpp"
#include "engine/entities/entity-manager.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/scenes/scene-transition-context.hpp"

namespace Core {

namespace Rendering {
class IRenderer;
}
}  // namespace Core

namespace SnakeGame {
class GameplayStateMachine;

struct GameplaySceneParams {
  Core::Events::IEventBus* eventBus;
};

class GameplayScene : public Core::Scenes::IGameScene {
 public:
  GameplayScene(const GameplaySceneParams& params);
  ~GameplayScene();
  void Initialize() override;
  void OnEnter(Core::Scenes::SceneTransitionContext ctx) override;
  void OnExit() override;
  void Update(float deltaTime) override;
  void OnRender(const Core::Rendering::IRenderer& renderer) const override;
  void DebugUpdate() const override;
  void DebugRender() const override;

 private:
  Core::Scenes::SceneTransitionContext transition;
  Renderer2D::RenderComponent2DManager renderComponentManager;
  Engine::Entities::EntityManager entityManager;
  GameplayStateMachine stateMachine;
  Core::Events::IEventBus& eventBus;
};
}  // namespace SnakeGame
