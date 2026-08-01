//
// Created by Dean Wilson 22 March 2026
//

#pragma once

#include "core/entities/i-entity-manager.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/scenes/i-scene.hpp"
#include "core/scenes/scene-lifetime.hpp"
#include "core/scenes/i-scene-manager.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/scenes/scene-transition-context.hpp"
#include "core/systems/i-game-system-manager.hpp"
#include "engine/systems/system.hpp"

#include <vector>
#include <memory>
#include <unordered_map>

namespace Core {
namespace Rendering {
class IRenderer;
}
}  // namespace Core

namespace Engine {

namespace Scenes {

class SceneManager : public Core::Scenes::ISceneManager, public Engine::Systems::System {
 public:
  SceneManager(
      Core::Events::IEventBus& eventBus, Core::Systems::IGameSystemManager& gameSystemManager,
      Core::Entities::IEntityManager& entityManager
  );
  ~SceneManager() = default;

  void Register(
      const std::string& name, Core::Scenes::SceneFactory factory,
      Core::Scenes::SceneLifetime lifetime = Core::Scenes::SceneLifetime::Persistent
  ) override;
  void SwitchTo(const std::string& name) override;
  void Push(const std::string& name) override;
  void Pop() override;

  virtual void OnUpdate(float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;
  virtual void OnRender(const Core::Rendering::IRenderer& renderer) const override;

 private:
  struct SceneEntry {
    Core::Scenes::SceneFactory factory;
    std::unique_ptr<Core::Scenes::IScene> instance;
    Core::Scenes::SceneLifetime lifetime;
  };

  Core::Events::IEventBus& eventBus;
  Core::Systems::IGameSystemManager& gameSystemManager;
  Core::Entities::IEntityManager& entityManager;

  Core::Scenes::IScene* ResolveScene(const std::string& name);
  Core::Scenes::SceneTransitionContext MakeContext();

  std::unordered_map<std::string, SceneEntry> registry;
  Core::Scenes::IScene* activeScene = nullptr;
  std::vector<Core::Scenes::IScene*> overlayStack;
};

}  // namespace Scenes
}  // namespace Engine
