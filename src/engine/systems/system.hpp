//
// Created by Dean Wilson on 26th July 2026.
//

#pragma once

#include "core/systems/i-system.hpp"

namespace Engine::Systems {
class System : public Core::Systems::ISystem {
 public:
  System();
  virtual void OnUpdate(const float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;
  virtual void OnRegistration() override;
};
}  // namespace Engine::Systems
