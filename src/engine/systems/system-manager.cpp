#include "system-manager.hpp"
#include <memory>
#include "core/utils/register-into.hpp"

namespace Engine::Systems {

SystemManager::SystemManager() {}

Core::Systems::ISystem* SystemManager::AddSystem(std::unique_ptr<Core::Systems::ISystem> system)
{
  return Core::Utils::RegisterInto(this->systems, std::move(system));
};

void SystemManager::RemoveSystem(Core::Systems::ISystem* system)
{
  std::erase_if(this->systems, [&](auto& s) { return s.get() == system; });
}

void SystemManager::OnUpdate(const float deltaTime)
{
  for (auto& system : this->systems) {
    system->OnUpdate(deltaTime);
  }
}

}  // namespace Engine::Systems
