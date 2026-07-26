//
// Created by Dean Wilson on 26th July 2026.
//

#pragma once

#include "core/entities/i-entity-manager.hpp"
#include "core/entities/i-entity.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/scenes/i-scene.hpp"
#include "core/systems/i-game-system.hpp"
#include "engine/systems/game-systems/game-system-manager.hpp"
#include <memory>

namespace Engine::Scenes {
class Scene : public Core::Scenes::IScene {
 public:
  explicit Scene();
  ~Scene() override = default;
  virtual void Render(const Core::Rendering::IRenderer&) const override;
  virtual void Update(const float deltaTime) override;
  virtual void DebugUpdate() const override;
  virtual void DebugRender() const override;
  virtual void OnRegistration() override;

  void OnExit() final;

 protected:

  Core::Entities::IEntity* AddEntity(std::unique_ptr<Core::Entities::IEntity> entity);
  void RemoveEntity(Core::Entities::IEntity* entity);

  Core::Systems::IGameSystem* AddGameSystem(std::unique_ptr<Core::Systems::IGameSystem> system);
  Core::Systems::IGameSystem* RemoveGameSystem(std::unique_ptr<Core::Systems::IGameSystem> system);

  Core::Events::IEventBus& GetEventBus() const;

  virtual void OnSceneExit();

 private:
  Core::Entities::IEntityManager& entityManager;
  Engine::Systems::GameSystemManager& gameSystemManager;
  Core::Events::IEventBus& eventBus;

  std::vector<Core::Entities::IEntity*> ownedEntities;
  std::vector<Core::Systems::IGameSystem*> ownedGameSystems;
};

}  // namespace Engine::Scenes
