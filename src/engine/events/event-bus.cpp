#include "event-bus.hpp"
#include "core/events/i-event-bus.hpp"

namespace Engine::Events {

Core::Events::SubscriptionToken EventBus::SubscribeImplementation(
    std::type_index eventType, std::function<void(const std::any&)> listener
)
{
  Core::Events::SubscriptionToken token = this->nextToken++;
  this->listeners[eventType][token] = std::move(listener);
  return token;
}

void EventBus::UnsubscribeImplementation(
    std::type_index eventType, Core::Events::SubscriptionToken token
)
{
  auto eventListeners = this->listeners.find(eventType);
  if (eventListeners == this->listeners.end()) {
    return;
  }
  eventListeners->second.erase(token);
}

void EventBus::PublishImplementation(std::type_index eventType, const std::any& event)
{
  auto eventListeners = this->listeners.find(eventType);
  if (eventListeners == this->listeners.end()) {
    return;
  }
  for (auto& [token, listener] : eventListeners->second) {
    listener(event);
  }
}

}  // namespace Engine::Events
