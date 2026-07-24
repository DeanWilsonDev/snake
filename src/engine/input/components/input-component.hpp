//
// Created by Dean Wilson 24th July 2026
//

#pragma once

#include <functional>
#include <string>
#include "core/input/action-router.hpp"
#include "core/input/components/i-input-component.hpp"
#include "core/input/action-value.hpp"

namespace Core::Input {
class ActionRouters;
}

namespace Engine::Input::Components {

class InputComponent final : public Core::Input::Components::IInputComponent {
 public:
  explicit InputComponent();
  virtual void Bind(const std::string& name, std::function<void()> callback) override;

  virtual void BindAxis(
      const std::string& name, std::function<void(Core::Input::ActionValue)> callback,
      float threshold = 0.01f
  ) override;

  virtual void AttachRouter(Core::Input::ActionRouter& attachedRouter) override;

 private:
  Core::Input::ActionRouter* router;
  std::vector<Core::Input::ActionRouter::Handle> handles;
};

}  // namespace Engine::Input::Components
