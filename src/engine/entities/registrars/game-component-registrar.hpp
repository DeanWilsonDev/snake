//
// Created by Dean Wilson 2nd August 2026
//

#pragma once

#include "core/entities/i-component-registrar.hpp"
#include "engine/components/game-component.hpp"
#include "engine/entities/typed-component-registrar.hpp"

#include <memory>
#include <vector>

namespace Core::Components {
class IComponent;
}

namespace Engine::Entities::Registrars {
class GameComponentRegistrar final
    : public Engine::Entities::TypedComponentRegistrar<Engine::Components::GameComponent> {
 public:
  explicit GameComponentRegistrar() {}

 protected:
  void OnRegistered(Engine::Components::GameComponent* component) override;
  void OnUnregistered(Engine::Components::GameComponent* component) override;
  std::vector<Core::Components::IComponent*> GetComponentsFromRegistry() override;

 private:
  std::vector<std::unique_ptr<Engine::Components::GameComponent>> registry;
};

}  // namespace Engine::Entities::Registrars
