//
// Created by Dean Wilson on 25/8/2025.
//

#include "engine/entities/entity-manager.hpp"
#include "core/entities/i-entity.hpp"
#include "core/input/action-router.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "engine/entities/entity-activation-pipeline.hpp"
#include "engine/entities/entity-lifecycle-state.hpp"
#include <vector>

namespace Engine::Entities {

EntityManager::EntityManager(
    Core::Rendering::IRenderComponentManager* renderManager,
    Core::Input::ActionRouter& inputActionRouter
)
    : componentPipeline(renderManager, inputActionRouter)
{
}

Core::Entities::IEntity* EntityManager::AddEntity(std::unique_ptr<Core::Entities::IEntity> entity)
{
  Core::Entities::IEntity* handle = entity.get();
  this->componentPipeline.Run(handle);
  this->entities.push_back(std::move(entity));
  EntityLifecycleState state{this->beginPlayFiredIds, this->activeLastFrame};
  this->activationPipeline.Run(handle, state);
  return handle;
}

void EntityManager::RemoveEntity(Core::Entities::IEntity* entity)
{
  this->componentPipeline.Teardown(entity);
  std::erase_if(entities, [&](const auto& p) { return p.get() == entity; });
}

void EntityManager::OnUpdate(const float deltaTime)
{
  EntityLifecycleState state{this->beginPlayFiredIds, this->activeLastFrame};
  for (auto& object : this->entities) {
    this->activationPipeline.Run(object.get(), state);
    if (object->IsActive()) {
      object->Update(deltaTime);
    }
  }
}

void EntityManager::OnDebugUpdate() const
{
  for (auto& object : this->entities) {
    if (object->IsActive()) {
      object->DebugUpdate();
    }
  }
}

void EntityManager::OnDebugRender() const
{
  for (auto& object : this->entities) {
    if (object->IsActive()) {
      object->DebugRender();
    }
  }
}
}  // namespace Engine::Entities
