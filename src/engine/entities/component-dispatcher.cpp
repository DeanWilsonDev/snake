#include "component-dispatcher.hpp"
#include "core/entities/i-entity.hpp"

namespace Engine::Entities {

void ComponentDispatcher::Dispatch(Core::Entities::IEntity* entity)
{
  entity->ForEachComponent([this](const Core::Components::IComponent* component) {
    for (auto& [type, handler] : this->handlers) {
      handler(const_cast<Core::Components::IComponent*>(component));
    }
    return true;
  });
}

}  // namespace Engine::Entities
