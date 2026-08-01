//
// Created by Dean Wilson on 26th July 2026.
//

#pragma once

#include <memory>
#include "core/systems/i-game-system-manager.hpp"
#include "core/systems/i-game-system.hpp"
#include <vector>

namespace Engine::Systems {
class GameSystemManager : public Core::Systems::IGameSystemManager {
 public:
  GameSystemManager();
  virtual void OnUpdate(const float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;
  void OnRegistration() override;

  Core::Systems::IGameSystem* AddGameSystem(
      std::unique_ptr<Core::Systems::IGameSystem> gameSystem
  ) override;

  void RemoveGameSystem(Core::Systems::IGameSystem* gameSystem) override;

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
