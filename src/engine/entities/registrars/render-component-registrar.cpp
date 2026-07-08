#include "render-component-registrar.hpp"
#include "core/rendering/components/i-render-component.hpp"

namespace Engine::Entities::Registrars {

void RenderComponentRegistrar::OnRegistered(
    Core::Rendering::Components::IRenderComponent* component
)
{
  manager->Register(component);
}

void RenderComponentRegistrar::OnUnregistered(
    Core::Rendering::Components::IRenderComponent* component
)
{
  manager->Unregister(component);
}

}  // namespace Engine::Entities::Registrars
