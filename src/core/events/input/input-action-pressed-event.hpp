//
// Created by Dean Wilson on 22nd July 2026
//

#pragma once

#include "core/events/i-event.hpp"
#include "core/input/action.hpp"

namespace Core::Events::Input {
struct InputActionPressedEvent final : public Core::Events::IEvent {
  explicit InputActionPressedEvent(Core::Input::Action action): action(action){};
  Core::Input::Action action;
};
}  // namespace Core::Events::Input
