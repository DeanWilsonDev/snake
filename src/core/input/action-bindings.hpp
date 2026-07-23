//
// Created by Dean Wilson 23rd July 2026
//

#pragma once
#include <functional>
#include <unordered_map>
#include <string>
#include "core/life-cycle-hooks/i-updatable.hpp"

namespace Core::Events {
class IEventBus;
}

namespace Core::Input {
class ActionSet;
}

namespace Core {
namespace Input {

class ActionBindings: Core::IUpdatable {
 public:
  ActionBindings(Core::Events::IEventBus& eventBus, const ActionSet& actions);
  void Bind(const std::string& name, std::function<void()> callback);
  void BindAxis(const std::string& name, std::function<void()> callback);

  void Update();

 private:
  std::unordered_map<int, std::function<void()>> handlers;
};
}  // namespace Input
}  // namespace Core
