//
// Created by Dean Wilson on 22/9/2025.
//

#pragma once

#include "core/life-cycle-hooks/i-updatable.hpp"

namespace Core::Components {

class IComponent: public Core::IUpdatable {
  public:
    virtual ~IComponent() = default;
};

}  // namespace Core
