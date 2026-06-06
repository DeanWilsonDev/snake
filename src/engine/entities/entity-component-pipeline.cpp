#include "engine/entities/entity-component-pipeline.hpp"
#include "core/entities/i-entity.hpp"
#include "core/rendering/components/i-render-component.hpp"
#include "core/rendering/i-render-component-manager.hpp"

namespace Engine::Entities {

EntityComponentPipeline::EntityComponentPipeline(
    Core::Rendering::IRenderComponentManager* renderManager
)
{
  this->dispatcher.RegisterHandler<Core::Rendering::Components::IRenderComponent>(
      [renderManager](Core::Rendering::Components::IRenderComponent* component) {
        renderManager->Register(component);
      }
  );
}

void EntityComponentPipeline::Run(Core::Entities::IEntity* entity)
{
  entity->OnRegistration();
  this->dispatcher.Dispatch(entity);
}

}  // namespace Engine::Entities
