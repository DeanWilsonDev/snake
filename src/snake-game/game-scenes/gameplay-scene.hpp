///
/// Created by Dean Wilson 22 March 2026
///

#pragma once

#include "core/rendering/i-render-component-manager.hpp"
#include "core/scenes/i-scene.hpp"
#include "core/rendering/i-renderer.hpp"
#include "snake-game/settings/snake-game-settings.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "snake-game/game-state/gameplay-state-machine.hpp"
#include "engine/entities/entity-manager.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/scenes/scene-transition-context.hpp"
#include "snake-game/settings/snake-game-settings.hpp"

namespace Core {

namespace Rendering {
class IRenderer;
}
}  // namespace Core

namespace SnakeGame {
class GameplayStateMachine;

struct GameplaySceneParams {
  Core::Events::IEventBus& eventBus;
  Core::Rendering::IRenderComponentManager& renderComponentManager;
  const SnakeGameSettings& gameSettings;
  int screenWidth;
  int screenHeight;
};

class GameplayScene : public Core::Scenes::IScene {
 public:
  GameplayScene(const GameplaySceneParams& params);
  ~GameplayScene();
  void OnEnter(Core::Scenes::SceneTransitionContext ctx) override;
  void OnExit() override;
  void Update(float deltaTime) override;
  void OnRender(const Core::Rendering::IRenderer& renderer) const override;
  void DebugUpdate() const override;
  void DebugRender() const override;

 private:
  Core::Scenes::SceneTransitionContext transition;
  Core::Rendering::IRenderComponentManager& renderComponentManager;
  Engine::Entities::EntityManager entityManager;
  GameplayStateMachine stateMachine;
  Core::Events::IEventBus& eventBus;
  const SnakeGameSettings& gameSettings;
  int screenWidth;
  int screenHeight;
};
}  // namespace SnakeGame
