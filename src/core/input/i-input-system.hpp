//
// Created by Dean Wilson on 22nd July 2026.
//

#pragma once
#include "core/systems/i-system.hpp"

namespace Core::Input {
class ActionRouter;
}

namespace Core::Input {
class IInputSystem : public Core::Systems::ISystem {
 public:
  virtual ~IInputSystem() = default;
  virtual Core::Input::ActionRouter& GetActionRouter() = 0;
};
}  // namespace Core::Input
