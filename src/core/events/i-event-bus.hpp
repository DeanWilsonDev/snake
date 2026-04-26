///
/// Created by Dean Wilson 26th April 2026
///

#pragma once

#include <functional>
#include <typeindex>
#include <any>

namespace Core {
namespace Events {

using SubscriptionToken = size_t;

class IEventBus {
 public:
  virtual ~IEventBus() = default;

  template <typename TEvent>
  SubscriptionToken Subscribe(std::function<void(const TEvent&)> listener)
  {
    return SubscribeImplementation(typeid(TEvent), [listener](const std::any& event) {
      listener(std::any_cast<const TEvent&>(event));
    });
  };

  template <typename TEvent>
  void Unsubscribe(SubscriptionToken token)
  {
    return UnsubscribeImplementation(typeid(TEvent), token);
  }

  template <typename TEvent>
  void Publish(const TEvent& event)
  {
    return PublishImplementation(typeid(TEvent), event);
  }

 protected:
  virtual SubscriptionToken SubscribeImplementation(
      std::type_index eventType, std::function<void(const std::any&)> listener
  ) = 0;

  virtual void UnsubscribeImplementation(std::type_index eventType, SubscriptionToken token) = 0;

  virtual void PublishImplementation(std::type_index eventType, const std::any& event) = 0;
};
}  // namespace Events

}  // namespace Core
