//
// Created by Dean Wilson on 25/8/2025.
//

#include "engine/entities/entity-manager.hpp"
#include "core/entities/i-entity.hpp"
#include "core/rendering/components/i-render-component.hpp"
#include "core/rendering/i-render-manager.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include <vector>

namespace Engine::Entities {

EntityManager::EntityManager(Core::Rendering::IRenderComponentManager* renderManager)
    : pipeline(renderManager)
{
}

void EntityManager::AddEntity(Core::Entities::IEntity* entity)
{
  if (!entity) {
    return;
  }
  this->pipeline.Run(entity);
  this->entities.push_back(entity);
}

void EntityManager::OnUpdate(const float deltaTime)
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->Update(deltaTime);
    }
  }
}

void EntityManager::OnDebugUpdate() const
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->DebugUpdate();
    }
  }
}

void EntityManager::OnDebugRender() const
{
  for (auto* object : this->entities) {
    if (object->IsActive()) {
      object->DebugRender();
    }
  }
}
}  // namespace Engine::Entities
