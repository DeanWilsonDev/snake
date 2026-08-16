//
// Created by Dean Wilson on 2nd August 2026.
//

#pragma once

#include "engine/components/component.hpp"

namespace Engine::Components {

class GameComponent : public Engine::Components::Component {
 public:
  virtual void BeginPlay() override {};
  virtual void Update(const float) override {};
  virtual void DebugUpdate() const override {};
  virtual void DebugRender() const override {};
};

}  // namespace Engine::Components
