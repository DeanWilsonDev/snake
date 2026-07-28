//
// Created by Dean Wilson on 26th July 2026.
//

#pragma once

#include <memory>
#include "core/systems/i-game-system.hpp"
#include "engine/systems/system.hpp"
#include <vector>

namespace Engine::Systems {
class GameSystemManager : public Engine::Systems::System {
 public:
  GameSystemManager();
  virtual void OnUpdate(const float deltaTime) override;

  Core::Systems::IGameSystem* AddGameSystem(std::unique_ptr<Core::Systems::IGameSystem> gameSystem);

  void RemoveGameSystem(Core::Systems::IGameSystem* gameSystem);

  template <typename T>
  T* GetGameSystem()
  {
    for (auto& gameSystem : this->gameSystems) {
      if (auto* match = dynamic_cast<T*>(gameSystem.get())) {
        return match;
      }
      return nullptr;
    }
  }

 private:
  std::vector<std::unique_ptr<Core::Systems::IGameSystem>> gameSystems;
};
}  // namespace Engine::Systems
