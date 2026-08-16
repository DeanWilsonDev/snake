///
/// Created by Dean Wilson 2nd August 2026
///

#pragma once

#include "core/entities/entity-component-registrars.hpp"

namespace Core::Entities {
class IEntity;
}

namespace Engine::Entities {
struct EntityLifecycleState;

class ComponentUpdater {
 public:
  ComponentUpdater(Core::Entities::EntityComponentRegistrars& registrars);
  void Run(const float deltaTime, Core::Entities::IEntity* entity);

 private:
  Core::Entities::EntityComponentRegistrars& registrars;
};

}  // namespace Engine::Entities
