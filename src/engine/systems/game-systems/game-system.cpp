#include "engine/systems/game-systems/game-system.hpp"
#include "core/entities/i-entity-manager.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/entities/i-entity.hpp"

namespace Engine::Systems {
GameSystem::GameSystem(
    Core::Events::IEventBus& eventBus, Core::Entities::IEntityManager& entityManager
)
    : entityManager(entityManager), eventBus(eventBus) {};

void GameSystem::OnUpdate(const float) {};
void GameSystem::OnDebugUpdate() const {};
void GameSystem::OnDebugRender() const {};
void GameSystem::OnRegistration() {};

Core::Entities::IEntity* GameSystem::AddEntity(std::unique_ptr<Core::Entities::IEntity> entity)
{
  return this->entityManager.AddEntity(std::move(entity));
}

void GameSystem::RemoveEntity(Core::Entities::IEntity* entity)
{
  this->entityManager.RemoveEntity(entity);
}

Core::Events::IEventBus& GameSystem::GetEventBus() const
{
  return this->eventBus;
}

}  // namespace Engine::Systems
