#include "input-dispatcher.hpp"
#include <memory>
#include "core/events/i-event-bus.hpp"
#include "core/input/action.hpp"
#include "engine/events/input/input-action-pressed-event.hpp"
#include "engine/events/input/input-action-released-event.hpp"

namespace Engine::Input {

InputDispatcher::InputDispatcher(
    Core::Events::IEventBus& eventBus, std::vector<Core::Input::Action> actions
)
    : actions(actions), eventBus(eventBus)
{
  this->lastFrameDown.assign(this->actions.size(), false);
  this->currentDown.assign(this->actions.size(), false);
}

void InputDispatcher::AddSource(std::unique_ptr<Core::Input::IInputSource> source)
{
  this->sources.push_back(std::move(source));
}

void InputDispatcher::Run()
{
  for (size_t i = 0; i < this->actions.size(); ++i) {
    const auto& action = this->actions[i];

    bool isDown = false;
    for (auto& source : this->sources) {
      if (source->IsActionDown(action)) {
        isDown = true;
        break;
      }
    }

    this->currentDown[i] = isDown;
    bool wasDown = this->lastFrameDown[i];

    if (isDown != wasDown) {
      if (isDown) {
        this->eventBus.Publish(Engine::Events::Input::InputActionPressedEvent{action});
      }
      if (wasDown) {
        this->eventBus.Publish(Engine::Events::Input::InputActionReleasedEvent{action});
      }
    }
    this->lastFrameDown[i] = isDown;
  }
}

bool InputDispatcher::IsActionDown(Core::Input::Action action) const
{
  for (size_t i = 0; i < this->actions.size(); ++i) {
    if (this->actions[i].id == action.id) {
      return this->currentDown[i];
    }
  }
}

}  // namespace Engine::Input
