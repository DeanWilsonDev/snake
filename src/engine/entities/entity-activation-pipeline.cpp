
#include "engine/entities/entity-activation-pipeline.hpp"
#include "engine/entities/entity-lifecycle-state.hpp"
#include "engine/entities/entity-manager.hpp"

namespace Engine::Entities {

void EntityActivationPipeline::Run(Core::Entities::IEntity* entity, EntityLifecycleState& state)
{
  const int id = entity->GetID();
  const bool isActive = entity->IsActive();
  const bool wasActive = state.activeLastFrame.count(id) > 0;

  if (!wasActive && isActive) {
    entity->OnActivate();
    if (!state.beginPlayFiredIds.count(id)) {
      entity->BeginPlay();
      state.beginPlayFiredIds.insert(id);
    }
    state.activeLastFrame.insert(id);
  }
  else if (wasActive && !isActive) {
    state.activeLastFrame.erase(id);
  }
}

}  // namespace Engine::Entities
