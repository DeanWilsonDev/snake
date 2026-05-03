//
// Created by Dean Wilson on 25/8/2025.
//

#include "engine/entity/game-entity-manager.hpp"
#include "core/entity/i-entity.hpp"
#include "core/rendering/components/i-render-component.hpp"
#include "core/rendering/i-render-manager.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include <vector>

namespace Engine::Entity {

GameEntityManager::GameEntityManager(Core::Rendering::IRenderComponentManager* renderManager)
    : renderManager(renderManager)
{
}

void GameEntityManager::AddEntity(Core::Entity::IEntity* entity)
{
  if (!entity) {
    return;
  }
  this->entities.push_back(entity);
  this->renderManager->Register(
      entity->GetComponent<Core::Rendering::Components::IRenderComponent>()
  );
}

void GameEntityManager::OnUpdate(const float deltaTime)
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->Update(deltaTime);
    }
  }
}

void GameEntityManager::OnDebugUpdate() const
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->DebugUpdate();
    }
  }
}

void GameEntityManager::OnDebugRender() const
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->DebugRender();
    }
  }
}

void GameEntityManager::OnRender(const Core::Rendering::IRenderer& renderer) const
{
  this->renderManager->OnRender(renderer);
}

}  // namespace Engine::Entity
