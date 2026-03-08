//
// Created by Dean Wilson on 25/8/2025.
//

#include "core/entity/game-entity-manager.hpp"
#include "core/entity/entity.hpp"
#include "core/components/i-render-component-2d.hpp"
#include "core/render-component-2d-manager.hpp"
#include <vector>

namespace Core {

GameEntityManager::GameEntityManager(const RenderComponent2DManager& renderManager)
    : renderManager(renderManager)
{
}

void GameEntityManager::AddEntity(Entity::Entity* entity)
{
  this->entities.push_back(entity);
  this->renderManager.Register(entity->GetComponent<Component::IRenderComponent2D>());
}

void GameEntityManager::Update(const float deltaTime)
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->Update(deltaTime);
    }
  }
}

void GameEntityManager::DebugUpdate()
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->DebugUpdate();
    }
  }
}

void GameEntityManager::Render() const
{
  this->renderManager.RenderAll();
}

}  // namespace Core
