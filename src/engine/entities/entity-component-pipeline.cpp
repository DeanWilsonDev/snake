#include "engine/entities/entity-component-pipeline.hpp"
#include <memory>
#include "core/entities/i-entity.hpp"
#include "core/input/action-router.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "engine/entities/component-dispatcher.hpp"
#include "engine/entities/registrars/game-component-registrar.hpp"
#include "engine/entities/registrars/input-component-registrar.hpp"
#include "engine/entities/registrars/render-component-registrar.hpp"

namespace Engine::Entities {

EntityComponentPipeline::EntityComponentPipeline(
    Core::Rendering::IRenderComponentManager* renderManager,
    Core::Input::ActionRouter& inputActionRouter
)
    : dispatcher(ComponentDispatcher(registrars)), updater(ComponentUpdater(registrars))
{
  this->AddRegistrar(std::make_unique<Registrars::RenderComponentRegistrar>(renderManager));
  this->AddRegistrar(std::make_unique<Registrars::InputComponentRegistrar>(inputActionRouter));
  this->AddRegistrar(std::make_unique<Registrars::GameComponentRegistrar>());
}

void EntityComponentPipeline::AddRegistrar(
    std::unique_ptr<Core::Entities::IComponentRegistrar> registrar
)
{
  this->registrars.push_back(std::move(registrar));
}

void EntityComponentPipeline::Run()
{
  this->entity->OnRegistration();
  this->dispatcher.Dispatch(this->entity);
}

void EntityComponentPipeline::OnUpdate(const float deltaTime)
{
  this->updater.Run(deltaTime, this->entity);
}

void EntityComponentPipeline::Teardown()
{
  this->dispatcher.Teardown(this->entity);

  if (this->entity) {
    this->entity = nullptr;
    delete this->entity;
  }
}

void EntityComponentPipeline::SetEntity(Core::Entities::IEntity* entity)
{
  this->entity = entity;
}

}  // namespace Engine::Entities
