//
// Created by Dean Wilson on 26th July 2026.
//

#pragma once

#include "core/events/i-event-bus.hpp"
#include "core/systems/i-game-system.hpp"

namespace Engine::Systems {
class GameSystem : public Core::Systems::IGameSystem {
 public:
  GameSystem(Core::Events::IEventBus& eventBus);
  virtual void OnUpdate(const float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;
  virtual void OnRegistration() override;

 protected:
  Core::Events::IEventBus& eventBus;
};
}  // namespace Engine::Systems
