//
// Created by Dean Wilson on 25/8/2025.
//

#include "engine/entities/entity-manager.hpp"
#include "core/entities/i-entity.hpp"
#include "core/logging/log.hpp"
#include "core/rendering/components/i-render-component.hpp"
#include "core/rendering/i-render-manager.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include <vector>

namespace Engine::Entities {

EntityManager::EntityManager(Core::Rendering::IRenderComponentManager* renderManager)
    : renderManager(renderManager)
{
}

void EntityManager::AddEntity(Core::Entities::IEntity* entity)
{
  // SIDE QUEST: Entity Component Pipeline
  // AddEntity should only register entities. The engine should handle component
  // routing automatically via a ComponentDispatcher that inspects each entity's
  // components on registration and forwards them to the appropriate subsystems
  // (e.g. IRenderComponent -> RenderComponent2DManager). Scenes stay declarative.

  if (!entity) {
    return;
  }
  entity->OnRegistration();

  this->entities.push_back(entity);

  auto* renderComponent = entity->GetComponent<Core::Rendering::Components::IRenderComponent>();

  LOG_CORE_TRACE(
      "[EntityManager] AddEntity - render component: [{}]", static_cast<void*>(renderComponent)
  );

  this->renderManager->Register(renderComponent);
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

void EntityManager::OnRender(const Core::Rendering::IRenderer& renderer) const
{
  this->renderManager->OnRender(renderer);
}

}  // namespace Engine::Entities
