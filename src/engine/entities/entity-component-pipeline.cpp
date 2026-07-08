#include "engine/entities/entity-component-pipeline.hpp"
#include <memory>
#include "core/entities/i-entity.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "engine/entities/registrars/render-component-registrar.hpp"

namespace Engine::Entities {

EntityComponentPipeline::EntityComponentPipeline(
    Core::Rendering::IRenderComponentManager* renderManager
)
{
  this->dispatcher.AddRegistrar(
      std::make_unique<Registrars::RenderComponentRegistrar>(renderManager)
  );
}

void EntityComponentPipeline::Run(Core::Entities::IEntity* entity)
{
  entity->OnRegistration();
  this->dispatcher.Dispatch(entity);
}

void EntityComponentPipeline::Teardown(Core::Entities::IEntity* entity)
{
  this->dispatcher.Teardown(entity);
}

}  // namespace Engine::Entities
