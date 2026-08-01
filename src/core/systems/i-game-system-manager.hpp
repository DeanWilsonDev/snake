//
// Created by Dean Wilson on 1st August 2026.
//

#pragma once

#include <memory>
#include "core/systems/i-game-system.hpp"
#include "core/systems/i-system.hpp"

namespace Core::Systems {
class IGameSystemManager : public Core::Systems::ISystem {
 public:
  virtual ~IGameSystemManager() = default;
  virtual Core::Systems::IGameSystem* AddGameSystem(
      std::unique_ptr<Core::Systems::IGameSystem> gameSystem
  ) = 0;

  virtual void RemoveGameSystem(Core::Systems::IGameSystem* gameSystem) = 0;

  template <typename T>
  T* GetGameSystem();
};
}  // namespace Core::Systems
