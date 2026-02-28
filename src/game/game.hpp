//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once
#include <memory>
#include <vector>
#include <core/i-debugable.hpp>
#include <core/i-updatable.hpp>
#include "core/i-game.hpp"
#include "core/entity/game-entity-manager.hpp"
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
  std::unique_ptr<GameSettings> settings{nullptr};
  Engine::Config::ProjectSettings& projectSettings;
  Renderer2D::RenderComponent2DManager& renderManager;
  std::shared_ptr<Core::GameEntityManager> gameEntityManager;
  std::shared_ptr<GameplayStateMachine> gameplayStateMachine;
  std::unique_ptr<Snake> snake{nullptr};
  std::unique_ptr<Apple> apple{nullptr};

  std::vector<Core::IDebugable*> debugables{};
  std::vector<Core::IUpdatable*> updatables{};
};

}  // namespace Game
