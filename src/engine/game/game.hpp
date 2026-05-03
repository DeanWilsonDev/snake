//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once
#include <memory>
#include <vector>
#include <core/debug/i-debugable.hpp>
#include <core/i-updatable.hpp>
#include "core/i-game.hpp"
#include "engine/entity/game-entity-manager.hpp"
#include "engine/scenes/scene-manager.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/user-interface/i-user-interface-manager.hpp"

namespace Core {
class UserInterfaceManager;

namespace Math {
struct Transform2D;
struct Vector2D;
}  // namespace Math
namespace Geometry {
struct Rectangle;
}  // namespace Geometry

namespace Rendering {
class IRenderComponentManager;
class IRenderer;
namespace Components {
class IRenderComponent2D;
}
}  // namespace Rendering
}  // namespace Core

namespace Engine {
class DependencyInjector;

namespace Config {
struct ProjectSettings;

}

class Game : public Core::IGame {
 public:
  explicit Game(
      Engine::DependencyInjector& injector, Engine::Config::ProjectSettings& projectSettings,
      Core::Rendering::IRenderComponentManager& renderManager
  );

  ~Game() override;

  void Initialize() override;
  void OnUpdate(float deltaTime) override;
  void OnRender(const Core::Rendering::IRenderer& rendrer) const override;
  void OnDebugUpdate() const override;
  void OnDebugRender() const override;

 protected:
  Engine::Scenes::SceneManager& GetSceneManager();

 private:
  // std::unique_ptr<GameSettings> settings{nullptr};
  std::unique_ptr<Engine::Entity::GameEntityManager> gameEntityManager;
  std::unique_ptr<Engine::Scenes::SceneManager> sceneManager;
  // std::unique_ptr<GameplayStateMachine> gameplayStateMachine;
  Engine::Config::ProjectSettings& projectSettings;

  std::vector<Core::Debug::IDebugable*> debugables{};
  std::vector<Core::IUpdatable*> updatables{};

  Engine::DependencyInjector* injector;
  std::shared_ptr<Core::UserInterface::IUserInterfaceManager> userInterfaceManager;
  std::shared_ptr<Core::Rendering::IRenderComponentManager> renderManager;
  std::shared_ptr<Core::Rendering::IRenderer> renderer;
};

}  // namespace Engine
