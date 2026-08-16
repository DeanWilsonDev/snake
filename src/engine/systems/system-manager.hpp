//
// Created by Dean Wilson on 26th July 2026.
//

#pragma once

#include <memory>
#include "engine/systems/system.hpp"
#include <vector>

namespace Engine::Systems {
class SystemManager : public Engine::Systems::System {
 public:
  SystemManager();
  virtual void OnUpdate(const float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;

  Core::Systems::ISystem* AddSystem(std::unique_ptr<Core::Systems::ISystem> system);
  void RemoveSystem(Core::Systems::ISystem* system);

  template <typename T>
  T* GetSystem()
  {
    for (auto& system : systems) {
      if (auto* match = dynamic_cast<T*>(system.get())) {
        return match;
      }
      return nullptr;
    }
  }

  template <typename T, typename... Args>
  T* CreateSystem(Args&&... args)
  {
    auto system = std::make_unique<T>(std::forward<Args>(args)...);
    T* raw = system.get();
    this->AddSystem(std::move(system));
    return raw;
  }

 private:
  std::vector<std::unique_ptr<Core::Systems::ISystem>> systems;
};
}  // namespace Engine::Systems
