#include "game-component-registrar.hpp"
#include <memory>
#include <vector>
#include "core/logging/log.hpp"

namespace Engine::Entities::Registrars {

void GameComponentRegistrar::OnRegistered(Engine::Components::GameComponent* component)
{
  LOG_CORE_DEBUG(
      "[GameComponentRegistrar] Adding Game Component: {}", static_cast<void*>(component)
  );
  this->registry.emplace_back(component);
}

void GameComponentRegistrar::OnUnregistered(Engine::Components::GameComponent* component)
{
  std::erase_if(this->registry, [&](auto& c) { return c.get() == component; });
}

std::vector<Core::Components::IComponent*> GameComponentRegistrar::GetComponentsFromRegistry()
{
  std::vector<Core::Components::IComponent*> raw;
  raw.reserve(this->registry.size());
  for (const auto& owner : this->registry) {
    raw.push_back(owner.get());
  }
  return raw;
}

}  // namespace Engine::Entities::Registrars
