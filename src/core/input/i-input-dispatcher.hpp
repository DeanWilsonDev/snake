//
// Created by Dean Wilson on 22nd July 2026
//

#pragma once

#include <memory>
#include "core/input/i-input-source.hpp"
#include "core/systems/i-dispatcher.hpp"

namespace Core::Input {
class IInputDispatcher : public Systems::IDispatcher {
 public:
  virtual ~IInputDispatcher() = default;
  virtual void AddSource(std::unique_ptr<IInputSource> source) = 0;
  virtual Core::Input::ActionValue GetActionValue(Core::Input::Action action) const = 0;
};
}  // namespace Core::Input
