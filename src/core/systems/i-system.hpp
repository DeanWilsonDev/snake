//
// Created by Dean Wilson on 22nd July 2026.
//

#pragma once

#include "core/debug/i-on-debugable.hpp"
#include "core/life-cycle-hooks/i-on-updatable.hpp"

namespace Core::Systems {
class ISystem : public IOnUpdatable, public Debug::IOnDebugable {
 public:
  virtual ~ISystem() = default;
};
}  // namespace Core::Systems
