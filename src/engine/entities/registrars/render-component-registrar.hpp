//
// Created by Dean Wilson 8th July 2026
//

#pragma once

#include "core/rendering/components/i-render-component.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "engine/entities/typed-component-registrar.hpp"

#include <memory>
#include <vector>

namespace Core::Components {
class IComponent;
}

namespace Engine::Entities::Registrars {
class RenderComponentRegistrar final
    : public TypedComponentRegistrar<Core::Rendering::Components::IRenderComponent> {
 public:
  explicit RenderComponentRegistrar(Core::Rendering::IRenderComponentManager* manager)
      : manager(manager)
  {
  }

 protected:
  void OnRegistered(Core::Rendering::Components::IRenderComponent* component) override;
  void OnUnregistered(Core::Rendering::Components::IRenderComponent* component) override;
  std::vector<Core::Components::IComponent*> GetComponentsFromRegistry() override;

 private:
  Core::Rendering::IRenderComponentManager* manager;
  std::vector<std::unique_ptr<Core::Rendering::Components::IRenderComponent>> registry;
};

}  // namespace Engine::Entities::Registrars
