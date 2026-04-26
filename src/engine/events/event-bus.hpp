///
/// Created by Dean Wilson 26th April 2026
///

#pragma once

#include "core/events/i-event-bus.hpp"
#include <unordered_map>

namespace Engine {
namespace Events {
class EventBus : public Core::Events::IEventBus {
 public:
  EventBus() = default;
  ~EventBus() override = default;

 protected:
  Core::Events::SubscriptionToken SubscribeImplementation(
      std::type_index eventType, std::function<void(const std::any&)> listener
  ) override;

  void UnsubscribeImplementation(
      std::type_index eventType, Core::Events::SubscriptionToken token
  ) override;

  void PublishImplementation(std::type_index eventType, const std::any& event) override;

 private:
  using ListenerMap =
      std::unordered_map<Core::Events::SubscriptionToken, std::function<void(const std::any&)>>;
  std::unordered_map<std::type_index, ListenerMap> listeners;
  Core::Events::SubscriptionToken nextToken = 0;
};
}  // namespace Events
}  // namespace Engine
