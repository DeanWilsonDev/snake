///
/// Created by Dean Wilson 5th July 2026
///

#pragma once

namespace Core::Entities {
class IEntity;
}

namespace Engine::Entities {
struct EntityLifecycleState;

class EntityActivationPipeline {
 public:
  void Run(Core::Entities::IEntity* entity, EntityLifecycleState& state);
};

}  // namespace Engine::Entities
