#include "component-updater.hpp"
#include "core/entities/i-entity.hpp"

namespace Engine::Entities {

ComponentUpdater::ComponentUpdater(Core::Entities::EntityComponentRegistrars& registrars)
    : registrars(registrars)
{

}

void ComponentUpdater::Run(const float deltaTime, Core::Entities::IEntity* entity)
{
  entity->ForEachComponent([deltaTime](Core::Components::IComponent* component) {
    component->Update(deltaTime);
    component->DebugUpdate();
    component->DebugRender();
    return true;
  });
};

}  // namespace Engine::Entities
