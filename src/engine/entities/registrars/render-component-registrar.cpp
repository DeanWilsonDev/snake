#include "render-component-registrar.hpp"
#include "core/rendering/components/i-render-component.hpp"

namespace Engine::Entities::Registrars {

void RenderComponentRegistrar::OnRegistered(
    Core::Rendering::Components::IRenderComponent* component
)
{
  this->manager->Register(component);
}

void RenderComponentRegistrar::OnUnregistered(
    Core::Rendering::Components::IRenderComponent* component
)
{
  this->manager->Unregister(component);
  std::erase_if(this->registry, [&](auto& c) { return c.get() == component; });
}

std::vector<Core::Components::IComponent*> RenderComponentRegistrar::GetComponentsFromRegistry()
{
  std::vector<Core::Components::IComponent*> raw;
  raw.reserve(this->registry.size());
  for (const auto& owner : this->registry) {
    raw.push_back(owner.get());
  }
  return raw;
}

}  // namespace Engine::Entities::Registrars
