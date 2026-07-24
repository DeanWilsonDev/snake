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

}  // namespace Engine::Entities::Registrars
