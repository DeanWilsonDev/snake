#include "input-component-registrar.hpp"
#include "core/input/components/i-input-component.hpp"

namespace Engine::Entities::Registrars {

InputComponentRegistrar::InputComponentRegistrar(Core::Input::ActionRouter& router) : router(router)
{
}

void InputComponentRegistrar::OnRegistered(Core::Input::Components::IInputComponent* component)
{
  component->AttachRouter(this->router);
}

void InputComponentRegistrar::OnUnregistered(Core::Input::Components::IInputComponent*) {}

std::vector<Core::Components::IComponent*> InputComponentRegistrar::GetComponentsFromRegistry()
{
  std::vector<Core::Components::IComponent*> raw;
  raw.reserve(this->registry.size());
  for (const auto& owner : this->registry) {
    raw.push_back(owner.get());
  }
  return raw;
}

}  // namespace Engine::Entities::Registrars
