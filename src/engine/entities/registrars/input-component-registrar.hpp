//
// Created by Dean Wilson 8th July 2026
//

#pragma once

#include "core/input/components/i-input-component.hpp"
#include "engine/entities/typed-component-registrar.hpp"

namespace Core::Components {
class IComponent;
}

namespace Core::Input {
class ActionRouter;
}

namespace Core::Input::Components {
class IInputComponent;
}

namespace Engine::Entities::Registrars {
class InputComponentRegistrar final
    : public TypedComponentRegistrar<Core::Input::Components::IInputComponent> {
 public:
  explicit InputComponentRegistrar(Core::Input::ActionRouter& router);

 protected:
  void OnRegistered(Core::Input::Components::IInputComponent* component) override;
  void OnUnregistered(Core::Input::Components::IInputComponent* component) override;

 private:
  Core::Input::ActionRouter& router;
};

}  // namespace Engine::Entities::Registrars
