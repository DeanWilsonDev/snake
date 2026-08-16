//
// Created by Dean Wilson on 25/8/2025.
//

#include "engine/entities/entity-manager.hpp"
#include "core/entities/i-entity.hpp"
#include "core/input/action-router.hpp"
#include "core/logging/log.hpp"
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

void EntityManager::OnRegistration()
{
  // This is for registrations on the EntityManager itself, not the entities it holds
}

Core::Entities::IEntity* EntityManager::AddEntity(std::unique_ptr<Core::Entities::IEntity> entity)
{
  Core::Entities::IEntity* handle = entity.get();
  this->componentPipeline.SetEntity(handle);
  this->componentPipeline.Run();
  this->entities.push_back(std::move(entity));
  EntityLifecycleState state{this->beginPlayFiredIds, this->activeLastFrame};
  this->activationPipeline.Run(handle, state);
  return handle;
}

void EntityManager::RemoveEntity(Core::Entities::IEntity* entity)
{
  this->componentPipeline.SetEntity(entity);
  this->componentPipeline.Teardown();
  std::erase_if(entities, [&](const auto& p) { return p.get() == entity; });
}

void EntityManager::OnUpdate(const float deltaTime)
{
  EntityLifecycleState state{this->beginPlayFiredIds, this->activeLastFrame};
  for (auto& entity : this->entities) {
    // SIDE QUEST: Make this event driven so that if "active" becomes true it fires

    this->activationPipeline.Run(entity.get(), state);

    if (entity->IsActive()) {
      entity->Update(deltaTime);
      this->componentPipeline.SetEntity(entity.get());
      this->componentPipeline.OnUpdate(deltaTime);
    }
  }
}

void EntityManager::OnDebugUpdate() const
{
  for (auto& entity : this->entities) {
    if (entity->IsActive()) {
      entity->DebugUpdate();
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
