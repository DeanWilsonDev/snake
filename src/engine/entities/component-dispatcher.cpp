#include "component-dispatcher.hpp"
#include "core/components/i-component.hpp"
#include "core/entities/entity-component-registrars.hpp"
#include "core/entities/i-entity.hpp"

namespace Engine::Entities {

ComponentDispatcher::ComponentDispatcher(Core::Entities::EntityComponentRegistrars& registrars)
    : registrars(registrars)
{
}

void ComponentDispatcher::Dispatch(Core::Entities::IEntity* entity)
{
  entity->ForEachComponent([this](const Core::Components::IComponent* component) {
    for (auto& registrar : this->registrars) {
      registrar->Register(const_cast<Core::Components::IComponent*>(component));
    }
    return true;
  });
}

void ComponentDispatcher::Teardown(Core::Entities::IEntity* entity)
{
  entity->ForEachComponent([this](const Core::Components::IComponent* component) {
    for (auto& registrar : this->registrars) {
      registrar->Unregister(const_cast<Core::Components::IComponent*>(component));
    }
    return true;
  });
}

}  // namespace Engine::Entities
