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
#include "core/render-component-2d-manager.hpp"
#include "core/user-interface-manager.hpp"

namespace Core {
class RenderComponent2DManager;
class UserInterfaceManager;

namespace Components {
class IRenderComponent2D;
}

namespace Core::Math {
struct Transform2D;
struct Vector2D;

namespace Geometry {
struct Rectangle;

}

}  // namespace Core::Math
}  // namespace Core

namespace Engine {
class DependencyInjector;

namespace Config {
struct ProjectSettings;

}
}  // namespace Engine

namespace Game {
class Snake;
class Apple;
class GameplayStateMachine;
struct GameSettings;

class Game final : public Core::IGame {
 public:
  explicit Game(
      Engine::DependencyInjector& injector, Engine::Config::ProjectSettings& projectSettings,
      Core::RenderComponent2DManager& renderManager
  );

  ~Game() override;

  void Initialize() override;
  void Update(float deltaTime) override;
  void Render() override;
  void DebugUpdate() override;
  void DebugRender() override;

 private:
  Engine::DependencyInjector& injector;
  std::unique_ptr<GameSettings> settings{nullptr};
  Engine::Config::ProjectSettings& projectSettings;
  Core::RenderComponent2DManager& renderManager;
  std::shared_ptr<Core::GameEntityManager> gameEntityManager;
  std::shared_ptr<Core::UserInterfaceManager> userInterfaceManager;
  std::shared_ptr<GameplayStateMachine> gameplayStateMachine;
  std::unique_ptr<Snake> snake{nullptr};
  std::unique_ptr<Apple> apple{nullptr};

  std::vector<Core::IDebugable*> debugables{};
  std::vector<Core::IUpdatable*> updatables{};
};

}  // namespace Game
