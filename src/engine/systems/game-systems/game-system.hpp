//
// Created by Dean Wilson on 26th July 2026.
//

#pragma once

#include "core/entities/i-entity-manager.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/systems/i-game-system.hpp"

namespace Core::Entities {
class IEntityManager;
}

namespace Engine::Systems {
class GameSystem : public Core::Systems::IGameSystem {
 public:
  GameSystem(Core::Events::IEventBus& eventBus, Core::Entities::IEntityManager& entityManager);
  virtual void OnUpdate(const float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;
  virtual void OnRegistration() override;

  Core::Entities::IEntity* AddEntity(std::unique_ptr<Core::Entities::IEntity> entity);
  void RemoveEntity(Core::Entities::IEntity* entity);

  Core::Events::IEventBus& GetEventBus() const;

 private:
  Core::Entities::IEntityManager& entityManager;
  Core::Events::IEventBus& eventBus;
};
}  // namespace Engine::Systems
