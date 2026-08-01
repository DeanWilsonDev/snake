///
/// Created by Dean Wilson 22 March 2026
///

#pragma once

#include "core/rendering/i-render-component-manager.hpp"
#include "engine/scenes/scene.hpp"
#include "core/rendering/i-renderer.hpp"
#include "snake-game/game-systems/snake-spawn-system.hpp"
#include "snake-game/settings/snake-game-settings.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "snake-game/game-state/gameplay-state-machine.hpp"
#include "core/scenes/scene-transition-context.hpp"
#include "snake-game/settings/snake-game-settings.hpp"

namespace Core::Rendering {
class IRenderer;
}  // namespace Core::Rendering

namespace SnakeGame {
class Snake;
}

namespace Core::Entities {
class IEntityManager;
}

namespace SnakeGame {
class GameplayStateMachine;

struct GameplaySceneParams : public Engine::Scenes::SceneParams {
  // Core::Rendering::IRenderComponentManager& renderComponentManager;
  const SnakeGameSettings& gameSettings;
  const int screenWidth;
  const int screenHeight;
};

class GameplayScene : public Engine::Scenes::Scene {
 public:
  GameplayScene(const GameplaySceneParams& params);
  ~GameplayScene();
  void OnEnter(Core::Scenes::SceneTransitionContext ctx) override;
  void OnSceneExit() override;
  void Update(float deltaTime) override;
  void Render(const Core::Rendering::IRenderer& renderer) const override;
  void DebugUpdate() const override;
  void DebugRender() const override;

 private:
  Core::Scenes::SceneTransitionContext transition;
  // Core::Rendering::IRenderComponentManager& renderComponentManager;
  GameplayStateMachine stateMachine;

  std::unique_ptr<Snake> snake;
  const SnakeGameSettings& gameSettings;
  const int screenWidth;
  const int screenHeight;
};
}  // namespace SnakeGame
