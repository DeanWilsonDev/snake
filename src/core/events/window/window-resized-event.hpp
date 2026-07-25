//
// Created by Dean Wilson on 22nd July 2026
//

#pragma once

#include "core/events/i-event.hpp"

// SIDE QUEST: This is an example of an event for Window. 
// Window sizing isn't supported currently
namespace Engine::Events::Window {
struct WindowResizedEvent final : public Core::Events::IEvent {
  // TODO: To be implemented
};
}  // namespace Engine::Events::Window
