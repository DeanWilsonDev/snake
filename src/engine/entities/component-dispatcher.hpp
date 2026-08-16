//
// Created by Dean Wilson 6th June 2026
//

#pragma once

#include "core/entities/entity-component-registrars.hpp"
#include "core/entities/i-component-dispatcher.hpp"
#include "core/entities/i-entity.hpp"

namespace Engine::Entities {

class ComponentDispatcher final : public Core::Entities::IComponentDispatcher {
 public:
  ComponentDispatcher(Core::Entities::EntityComponentRegistrars&);
  ~ComponentDispatcher() = default;
  void Dispatch(Core::Entities::IEntity*) override;
  void Teardown(Core::Entities::IEntity*) override;

 private:
  Core::Entities::EntityComponentRegistrars& registrars;
};

}  // namespace Engine::Entities
