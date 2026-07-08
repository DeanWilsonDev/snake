//
// Created by Dean Wilson 6th June 2026
//

#pragma once

#include "core/entities/i-component-dispatcher.hpp"
#include "core/entities/i-component-registrar.hpp"
#include "core/entities/i-entity.hpp"
#include <memory>

namespace Engine::Entities {

class ComponentDispatcher final : public Core::Entities::IComponentDispatcher {
 public:
  ~ComponentDispatcher() = default;
  void Dispatch(Core::Entities::IEntity*) override;
  void Teardown(Core::Entities::IEntity*) override;
  void AddRegistrar(std::unique_ptr<Core::Entities::IComponentRegistrar> registrar) override;

 private:
  std::vector<std::unique_ptr<Core::Entities::IComponentRegistrar>> registrars;
};

}  // namespace Engine::Entities
