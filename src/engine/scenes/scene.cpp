#include "scene.hpp"
#include <memory>
#include "core/rendering/i-renderer.hpp"
#include "engine/systems/game-systems/game-system-manager.hpp"
#include "engine/systems/game-systems/game-system.hpp"

namespace Engine::Scenes {

void Scene::Render(const Core::Rendering::IRenderer&) const {};
void Scene::Update(const float) {};
void Scene::DebugUpdate() const {};
void Scene::DebugRender() const {};
void Scene::OnRegistration() {};

Core::Entities::IEntity* Scene::AddEntity(std::unique_ptr<Core::Entities::IEntity> entity)
{
  auto* raw = this->entityManager.AddEntity(std::move(entity));
  this->ownedEntities.push_back(raw);
  return raw;
}

void Scene::RemoveEntity(Core::Entities::IEntity* entity)
{
  this->entityManager.RemoveEntity(entity);
  std::erase(this->ownedEntities, entity);
}

Core::Systems::IGameSystem* Scene::AddGameSystem(
    std::unique_ptr<Core::Systems::IGameSystem> gameSystem
)
{
  auto* raw = this->gameSystemManager.AddGameSystem(std::move(gameSystem));
  this->ownedGameSystems.push_back(raw);
  return raw;
}

void Scene::RemoveGameSystem(Core::Systems::IGameSystem* gameSystem)
{
  this->gameSystemManager.RemoveGameSystem(gameSystem);
  std::erase(this->ownedGameSystems, gameSystem);
}

void Scene::OnExit()
{
  for (auto* entity : this->ownedEntities) {
    this->RemoveEntity(entity);
  }

  for (auto* gameSystem : this->ownedGameSystems) {
    this->RemoveGameSystem(gameSystem);
  }

  this->ownedEntities.clear();
  this->ownedGameSystems.clear();
  this->OnSceneExit();
}

Core::Events::IEventBus& Scene::GetEventBus() const
{
  return this->eventBus;
}

Core::Entities::IEntityManager& Scene::GetEntityManager() const
{
  return this->entityManager;
}

}  // namespace Engine::Scenes
