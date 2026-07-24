//
// Created by Dean Wilson 23rd July 2026
//

#pragma once
#include <functional>
#include <string>
#include "core/life-cycle-hooks/i-updatable.hpp"
#include "core/input/action.hpp"
#include "core/input/action-value.hpp"
#include "core/input/i-input-dispatcher.hpp"

namespace Core::Events {
class IEventBus;
}

namespace Core::Input {
class ActionSet;
}

namespace Core {
namespace Input {

class ActionRouter : Core::IUpdatable {
 public:
  class Handle {
   public:
    Handle() = default;
    Handle(const Handle&) = delete;
    Handle& operator=(const Handle&) = delete;
    Handle(Handle&& other) noexcept { *this = std::move(other); };
    Handle& operator=(Handle&& other) noexcept
    {
      if (this != &other) {
        Release();
        this->owner = other.owner;
        this->id = other.id;
        other.owner = nullptr;
      }
      return *this;
    }
    ~Handle() { Release(); }

   private:
    friend class ActionRouter;
    Handle(ActionRouter* owner, int id) : owner(owner), id(id) {};
    void Release()
    {
      if (this->owner) this->owner->Unbind(this->id);
      this->owner = nullptr;
    };

    ActionRouter* owner = nullptr;
    int id = 0;
  };

  ActionRouter(
      Core::Events::IEventBus& eventBus, const ActionSet& actions,
      const IInputDispatcher& dispatcher
  );
  [[nodiscard]] Handle Bind(const std::string& name, std::function<void()> callback);
  [[nodiscard]] Handle BindAxis(
      const std::string& name, std::function<void(ActionValue)> callback, float threshold = 0.01f
  );
  void Update(const float deltaTime) override;

 private:
  void Unbind(int handleId);

  struct DigitalBinding {
    int handleId;
    int actionId;
    std::function<void()> callback;
  };

  struct AxisBinding {
    int handleId;
    Core::Input::Action action;
    std::function<void(Core::Input::ActionValue)> callback;
    Core::Input::ActionValue lastValue;
    float threshold;
  };

  std::vector<DigitalBinding> digitalBindings;
  std::vector<AxisBinding> axisBindings;
  int nextHandleId = 0;
  const ActionSet& actions;
  const IInputDispatcher& dispatcher;
};
}  // namespace Input
}  // namespace Core
