//
// Created by Dean Wilson 2nd February 2026
//

#pragma once

#include "core/events/i-event-bus.hpp"
#include "core/input/i-input-backend.hpp"
#include "core/input/key-map.hpp"
#include "core/systems/i-system.hpp"
#include "engine/input/input-dispatcher.hpp"

using namespace Core::Input;

namespace Engine {

namespace Input {

class InputSystem final : public Core::Systems::ISystem {
 public:
  InputSystem(IInputBackend& inputBackend, Core::Events::IEventBus& eventBus, const KeyMap& keyMap);
  void OnUpdate(const float deltaTime) override;
  void OnDebugUpdate() const override;
  void OnDebugRender() const override;

 private:
  InputDispatcher dispatcher;
};
}  // namespace Input

}  // namespace Engine
