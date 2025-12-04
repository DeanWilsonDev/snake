//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once
#include "../core/i-game.hpp"
#include "core/components/transform-component-2d.hpp"
#include "core/i-game-state.h"
#include "renderer-2d/render-component-2d-manager.hpp"

namespace Renderer2D::Component {
class IRenderComponent2D;
}
namespace Core::Math::Geometry {
struct Rectangle;
}
namespace Core::Math {
struct Transform2D;
}
namespace Core::Math {
struct Vector2D;
}
namespace Game {
struct GameSettings;
}
namespace Game {
class Snake;
class Apple;
class GameplayStateMachine;
}  // namespace Game
namespace Core {
class DependencyInjector;
}
namespace Renderer2D {
class RenderComponent2DManager;
}
namespace Engine::Config {
struct ProjectSettings;
}
namespace Game {

class Game final : public Core::IGame {
 public:
  explicit Game(
      Core::DependencyInjector& injector, Engine::Config::ProjectSettings& projectSettings,
      Renderer2D::RenderComponent2DManager& renderManager
  );

  ~Game() override;

  void Initialize() override;
  void Update(float deltaTime) override;
  void DebugUpdate() override;
  void Render() override;

 private:
  Core::DependencyInjector& injector;
  Engine::Config::ProjectSettings& projectSettings;
  Renderer2D::RenderComponent2DManager& renderManager;
  GameplayStateMachine* gameplayStateMachine{nullptr};
  GameSettings* settings{nullptr};
  Snake* snake{nullptr};
  Core::Components::TransformComponent2D* snakeTransformComponent{nullptr};
  Core::Math::Geometry::Rectangle* snakeBounds{nullptr};
  Apple* apple{nullptr};
  Core::Components::TransformComponent2D* appleTransformComponent{nullptr};
  Core::Math::Geometry::Rectangle* appleBounds{nullptr};
};

}  // namespace Game
