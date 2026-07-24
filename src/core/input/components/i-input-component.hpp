//
// Created by Dean Wilson 24th July 2026
//

#pragma once

#include <functional>
#include <string>
#include "core/components/i-component.hpp"
#include "core/input/action-value.hpp"

namespace Core::Input {
class ActionRouter;
}


namespace Core::Input::Components {

class IInputComponent : public Core::Components::IComponent {
 public:
  virtual void Bind(const std::string& name, std::function<void()> callback) = 0;

  virtual void BindAxis(
      const std::string& name, std::function<void(Core::Input::ActionValue)> callback,
      float threshold = 0.01f
  ) = 0;

  virtual void AttachRouter(Core::Input::ActionRouter& attachedRouter) = 0;
};

}  // namespace Core::Input::Components
