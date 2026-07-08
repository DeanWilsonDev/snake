//
// Created by Dean Wilson 8th July 2026
//

#pragma once

#include "core/entities/i-component-registrar.hpp"

namespace Core::Components {
class IComponent;
}

namespace Engine::Entities {
template <typename TComponent>
class TypedComponentRegistrar : public Core::Entities::IComponentRegistrar {
 public:
  void Register(Core::Components::IComponent* component) final
  {
    if (auto* typed = dynamic_cast<TComponent*>(component)) {
      this->OnRegistered(typed);
    }
  };

  void Unregister(Core::Components::IComponent* component) final
  {
    if (auto* typed = dynamic_cast<TComponent*>(component)) {
      this->OnUnregistered(typed);
    }
  };

 private:
  virtual void OnRegistered(TComponent* component) = 0;
  virtual void OnUnregistered(TComponent* component) = 0;
};

}  // namespace Engine::Entities
