//
// Created by Dean Wilson on 22nd July 2026.
//

#pragma once

#include "core/debug/i-on-debugable.hpp"
#include "core/life-cycle-hooks/i-on-registration.hpp"
#include "core/life-cycle-hooks/i-on-updatable.hpp"

namespace Core::Systems {
class IGameSystem : public IOnUpdatable, public Debug::IOnDebugable, public IOnRegistration {
 public:
  virtual ~IGameSystem() = default;
};
}  // namespace Core::Systems
