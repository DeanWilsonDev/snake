//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once
#include "../core/i-game.hpp"
#include "core/math/transform-2d.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"

#include <memory>

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
  void Render() override;
  void RegisterRenderComponent(Renderer2D::Component::IRenderComponent2D* component) const;

 private:
  Core::DependencyInjector& injector;
  Engine::Config::ProjectSettings& projectSettings;
  Renderer2D::RenderComponent2DManager& renderManager;
  GameplayStateMachine* gameplayStateMachine{nullptr};
  GameSettings* settings{nullptr};
  Snake* snake{nullptr};
  Core::Math::Transform2D* snakeTransform{nullptr};
  Core::Math::Geometry::Rectangle* snakeBounds{nullptr};
  Apple* apple{nullptr};
  Core::Math::Transform2D* appleTransform{nullptr};
  Core::Math::Geometry::Rectangle* appleBounds{nullptr};
};

}  // namespace Game
