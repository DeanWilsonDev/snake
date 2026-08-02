//
// Created by Dean Wilson on 2nd August 2026.
//

#pragma once

#include "core/components/i-component.hpp"

namespace Engine::Components {

class Component : public Core::Components::IComponent {
 public:
  virtual void Update(const float) override {};
};

}  // namespace Core::Components
