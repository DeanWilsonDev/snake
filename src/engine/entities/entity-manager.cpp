//
// Created by Dean Wilson on 25/8/2025.
//

#include "engine/entities/entity-manager.hpp"
#include "core/entities/i-entity.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "engine/entities/entity-activation-pipeline.hpp"
#include "engine/entities/entity-lifecycle-state.hpp"
#include <vector>

namespace Engine::Entities {

EntityManager::EntityManager(Core::Rendering::IRenderComponentManager* renderManager)
    : componentPipeline(renderManager)
{
}

void EntityManager::AddEntity(Core::Entities::IEntity* entity)
{
  if (!entity) {
    return;
  }
  this->componentPipeline.Run(entity);
  this->entities.push_back(entity);
  EntityLifecycleState state{this->beginPlayFiredIds, this->activeLastFrame};
  this->activationPipeline.Run(entity, state);
}

void EntityManager::OnUpdate(const float deltaTime)
{
  EntityLifecycleState state{this->beginPlayFiredIds, this->activeLastFrame};
  for (auto* object : this->entities) {
    this->activationPipeline.Run(object, state);
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
