#include "game-system-manager.hpp"
#include "core/utils/register-into.hpp"
#include <memory>

namespace Engine::Systems {

GameSystemManager::GameSystemManager() {}

void GameSystemManager::OnRegistration() {};

Core::Systems::IGameSystem* GameSystemManager::AddGameSystem(
    std::unique_ptr<Core::Systems::IGameSystem> gameSystem
)
{
  return Core::Utils::RegisterInto(this->gameSystems, std::move(gameSystem));
};

void GameSystemManager::RemoveGameSystem(Core::Systems::IGameSystem* gameSystem)
{
  std::erase_if(this->gameSystems, [&](auto& gs) { return gs.get() == gameSystem; });
}

void GameSystemManager::OnUpdate(const float deltaTime)
{
  for (auto& gameSystem : this->gameSystems) {
    gameSystem->OnUpdate(deltaTime);
  }
}

void GameSystemManager::OnDebugUpdate() const
{
  for (auto& gameSystem : this->gameSystems) {
    gameSystem->OnDebugUpdate();
  }
};

void GameSystemManager::OnDebugRender() const
{
  for (auto& gameSystem : this->gameSystems) {
    gameSystem->OnDebugRender();
  }
};

}  // namespace Engine::Systems
