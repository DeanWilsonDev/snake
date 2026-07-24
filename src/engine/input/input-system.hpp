//
// Created by Dean Wilson 2nd February 2026
//

#pragma once

#include "core/events/i-event-bus.hpp"
#include "core/input/action-set.hpp"
#include "core/input/i-input-backend.hpp"
#include "core/input/key-map.hpp"
#include "core/input/i-input-system.hpp"
#include "core/input/action-router.hpp"
#include "engine/input/input-dispatcher.hpp"

using namespace Core::Input;

namespace Engine {

namespace Input {

class InputSystem final : public Core::Input::IInputSystem {
 public:
  InputSystem(
      IInputBackend& inputBackend, Core::Events::IEventBus& eventBus, const KeyMap& keyMap,
      std::vector<Action> actions, const ActionSet& actionSet
  );
  void OnUpdate(const float deltaTime) override;
  void OnDebugUpdate() const override;
  void OnDebugRender() const override;
  Core::Input::ActionRouter& GetActionRouter() override;

 private:
  InputDispatcher dispatcher;
  Core::Input::ActionRouter actionRouter;
};
}  // namespace Input

}  // namespace Engine
