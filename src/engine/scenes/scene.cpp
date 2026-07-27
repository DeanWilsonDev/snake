#include "scene.hpp"
#include <memory>
#include "core/rendering/i-renderer.hpp"

namespace Engine::Scenes {

void Scene::Render(const Core::Rendering::IRenderer&) const {};
void Scene::Update(const float) {};
void Scene::DebugUpdate() const {};
void Scene::DebugRender() const {};
void Scene::OnRegistration() {};

Core::Entities::IEntity* Scene::AddEntity(std::unique_ptr<Core::Entities::IEntity> entity)
{
  auto* raw = entityManager.AddEntity(std::move(entity));
  ownedEntities.push_back(raw);
  return raw;
}

Core::Systems::IGameSystem* Scene::AddGameSystem(
    std::unique_ptr<Core::Systems::IGameSystem> gameSystem
)
{
  auto* raw = gameSystemManager.AddGameSystem(std::move(gameSystem));
  ownedGameSystems.push_back(raw);
  return raw;
}

void Scene::OnExit()
{
  for (auto* entity : this->ownedEntities) {
    this->entityManager.RemoveEntity(entity);
  }

  for (auto* gameSystem : this->ownedGameSystems) {
    this->gameSystemManager.RemoveGameSystem(gameSystem);
  }

  ownedEntities.clear();
  ownedGameSystems.clear();
  OnSceneExit();
}

}  // namespace Engine::Scenes
