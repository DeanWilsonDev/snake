//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "core/debug/i-on-debugable.hpp"
#include "core/life-cycle-hooks/i-on-updatable.hpp"
#include "engine/entities/entity-activation-pipeline.hpp"
#include "engine/entities/entity-component-pipeline.hpp"

#include <unordered_set>
#include <vector>

namespace Core {
namespace Entities {
class IEntity;
}
namespace Rendering {
class IRenderer;
class IRenderComponentManager;
}  // namespace Rendering
}  // namespace Core

namespace Engine {

namespace Entities {

class EntityManager : public Core::IOnUpdatable, Core::Debug::IOnDebugable {
 public:
  EntityManager(Core::Rendering::IRenderComponentManager* renderManager);
  void AddEntity(Core::Entities::IEntity* entity);
  void OnUpdate(float deltaTime) override;
  void OnDebugUpdate() const override;
  void OnDebugRender() const override;

 private:
  std::vector<Core::Entities::IEntity*> entities;
  EntityComponentPipeline componentPipeline;
  EntityActivationPipeline activationPipeline;
  std::unordered_set<int> beginPlayFiredIds;
  std::unordered_set<int> activeLastFrame;
};

}  // namespace Entities
}  // namespace Engine
