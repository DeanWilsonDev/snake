//
// Created by Dean Wilson 8th July 2026
//

#pragma once

namespace Core::Components{
  class IComponent;
}

namespace Core::Entities {
class IComponentRegistrar {
 public:
  virtual ~IComponentRegistrar() = default;
  virtual void Register(Core::Components::IComponent* component) = 0;
  virtual void Unregister(Core::Components::IComponent* component) = 0;
};

}  // namespace Core::Entities
