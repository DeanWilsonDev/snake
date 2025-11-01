//
// Created by Dean Wilson on 25/8/2025.
//

#include "core/entity/game-entity-manager.hpp"
#include "core/entity/entity.h"
#include "renderer-2d/components/i-render-component-2d.h"
#include "renderer-2d/render-component-2d-manager.hpp"
#include <vector>

namespace Core {

GameEntityManager::GameEntityManager(
    const std::vector<Entity::Entity*>& entities,
    const Renderer2D::RenderComponent2DManager& renderManager
)
    : entities(entities), renderManager(renderManager)
{
}

void GameEntityManager::AddEntity(Entity::Entity* entity)
{
  this->entities.push_back(entity);
  this->renderManager.Register(entity->GetComponent<Renderer2D::Component::IRenderComponent2D>());
}

void GameEntityManager::Update(const float deltaTime) const
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->Update(deltaTime);
    }
  }
}
void GameEntityManager::Render() const
{
  this->renderManager.RenderAll();
}

}  // namespace Core
