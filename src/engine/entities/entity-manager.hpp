//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "core/entities/i-entity-manager.hpp"
#include "core/input/action-router.hpp"
#include "engine/entities/entity-activation-pipeline.hpp"
#include "engine/entities/entity-component-pipeline.hpp"

#include <memory>
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

class EntityManager : public Core::Entities::IEntityManager {
 public:
  EntityManager(
      Core::Rendering::IRenderComponentManager* renderManager,
      Core::Input::ActionRouter& inputActionRouter
  );

  Core::Entities::IEntity* AddEntity(std::unique_ptr<Core::Entities::IEntity> entity) override;
  void RemoveEntity(Core::Entities::IEntity* entity) override;
  void OnUpdate(float deltaTime) override;
  void OnDebugUpdate() const override;
  void OnDebugRender() const override;
  void OnRegistration() override;

 private:
  std::vector<std::unique_ptr<Core::Entities::IEntity>> entities;
  EntityComponentPipeline componentPipeline;
  EntityActivationPipeline activationPipeline;
  std::unordered_set<int> beginPlayFiredIds;
  std::unordered_set<int> activeLastFrame;
};

}  // namespace Entities
}  // namespace Engine
