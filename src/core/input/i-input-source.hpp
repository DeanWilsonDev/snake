//
// Created by Dean Wilson on 22nd July 2026
//

#pragma once

#include "core/input/action.hpp"
#include "core/input/action-value.hpp"

namespace Core::Input {

class IInputSource {
 public:
  virtual ~IInputSource() = default;
  virtual bool IsActionDown(Action action) const = 0;
  virtual ActionValue GetActionValue(Action action) const = 0;
};
}  // namespace Core::Input
