//
// Created by Dean Wilson on 22/9/2025.
//

#pragma once

#include "core/debug/i-debugable.hpp"
#include "core/life-cycle-hooks/i-begin-play.hpp"
#include "core/life-cycle-hooks/i-updatable.hpp"

namespace Core::Components {

class IComponent: public Core::IUpdatable, public Core::IBeginPlay, public Core::Debug::IDebugable {
  public:
    virtual ~IComponent() = default;
};

}  // namespace Core
