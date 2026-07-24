#include "action-router.hpp"
#include <cassert>
#include <core/logging/log.hpp>
#include "core/events/i-event-bus.hpp"
#include "core/events/input/input-action-pressed-event.hpp"
#include "core/input/action-set.hpp"

namespace Core::Input {

ActionRouter::ActionRouter(
    Core::Events::IEventBus& eventBus, const ActionSet& actions, const IInputDispatcher& dispatcher
)
    : actions(actions), dispatcher(dispatcher)
{
  eventBus.Subscribe<Core::Events::Input::InputActionPressedEvent>([this](const auto& event) {
    for (auto& binding : this->digitalBindings) {
      if (binding.actionId == event.action.id) {
        binding.callback();
      }
    }
  });
}

ActionRouter::Handle ActionRouter::Bind(const std::string& name, std::function<void()> callback)
{
  int handleId = this->nextHandleId++;
  this->digitalBindings.push_back({handleId, this->actions.Get(name).id, std::move(callback)});
  return Handle(this, handleId);
}

ActionRouter::Handle ActionRouter::BindAxis(
    const std::string& name, std::function<void(ActionValue)> callback, float threshold
)
{
  int handleId = this->nextHandleId++;
  this->axisBindings.push_back(
      {handleId, this->actions.Get(name), std::move(callback), ActionValue{}, threshold}
  );
  return Handle(this, handleId);
}

void ActionRouter::Update(const float)
{
  for (auto& binding : this->axisBindings) {
    ActionValue current = this->dispatcher.GetActionValue(binding.action);
    if (Distance(current, binding.lastValue) > binding.threshold) {
      binding.callback(current);
      binding.lastValue = current;
    }
  }
}

void ActionRouter::Unbind(int handleId)
{
  std::erase_if(this->digitalBindings, [&](auto& binding) { return binding.handleId == handleId; });
  std::erase_if(this->axisBindings, [&](auto& binding) { return binding.handleId == handleId; });
}

}  // namespace Core::Input
