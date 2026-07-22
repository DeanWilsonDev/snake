//
// Created by Dean Wilson on 22nd July 2026
//

#pragma once

#include "core/events/i-event.hpp"
#include "core/input/action.hpp"

namespace Engine::Events::Input {
struct InputActionReleasedEvent final : public Core::Events::IEvent {
 public:
  Core::Input::Action action;
};
}  // namespace Engine::Events::Input
