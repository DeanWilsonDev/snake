#include "component-updater.hpp"

namespace Engine::Entities {

ComponentUpdater::ComponentUpdater(Core::Entities::EntityComponentRegistrars& registrars)
    : registrars(registrars)
{
}

void ComponentUpdater::Run(const float deltaTime)
{
  for (auto& registrar : this->registrars) {
    for (auto& component : registrar->GetComponentsFromRegistry()) {
      component->Update(deltaTime);
    }
  }
};

}  // namespace Engine::Entities
