#include "input-dispatcher.hpp"
#include <memory>
#include "core/events/i-event-bus.hpp"
#include "core/input/action.hpp"
#include "engine/events/input/input-action-pressed-event.hpp"
#include "engine/events/input/input-action-released-event.hpp"

namespace Engine::Input {

InputDispatcher::InputDispatcher(Core::Events::IEventBus& eventBus) : eventBus(eventBus) {}

void InputDispatcher::AddSource(std::unique_ptr<Core::Input::IInputSource> source)
{
  this->sources.push_back(std::move(source));
}

void InputDispatcher::Run()
{
  for (size_t i = 0; i < static_cast<size_t>(Core::Input::Action::Count); ++i) {
    auto action = static_cast<Core::Input::Action>(i);

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
        this->eventBus.Publish(Events::Input::InputActionPressedEvent());
      }
      if (wasDown) {
        this->eventBus.Publish(Events::Input::InputActionReleasedEvent());
      }
    }
  }
}

bool InputDispatcher::IsActionDown(Core::Input::Action action) const
{
  return this->currentDown[static_cast<size_t>(action)];
}

}  // namespace Engine::Input
