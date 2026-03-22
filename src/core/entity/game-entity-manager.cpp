//
// Created by Dean Wilson on 25/8/2025.
//

#include "core/entity/game-entity-manager.hpp"
#include "core/entity/entity.hpp"
#include "core/rendering/components/i-render-component.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/rendering/render-component-2d-manager.hpp"
#include <vector>

namespace Core {

GameEntityManager::GameEntityManager(Rendering::RenderComponent2DManager* renderManager)
    : renderManager(renderManager)
{
}

void GameEntityManager::AddEntity(Entity::Entity* entity)
{
  if (!entity) {
    return;
  }
  this->entities.push_back(entity);
  this->renderManager->Register(entity->GetComponent<Rendering::Components::IRenderComponent>());
}

void GameEntityManager::OnUpdate(const float deltaTime)
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->Update(deltaTime);
    }
  }
}

void GameEntityManager::OnDebugUpdate()
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->DebugUpdate();
    }
  }
}

void GameEntityManager::OnRender(const Rendering::IRenderer& renderer)
{
  this->renderManager->Render(renderer);
}

}  // namespace Core
