//
// Created by Dean Wilson 6th June 2026
//

#pragma once

#include "core/entities/i-component-dispatcher.hpp"
#include "core/entities/i-entity-component-pipeline.hpp"
#include "core/entities/i-entity.hpp"
#include "engine/entities/component-dispatcher.hpp"

namespace Core::Rendering {
class IRenderComponentManager;
}  // namespace Core::Rendering

namespace Engine::Entities {

class EntityComponentPipeline : public Core::Entities::IEntityComponentPipeline {
 public:
  EntityComponentPipeline(Core::Rendering::IRenderComponentManager* renderManager);
  ~EntityComponentPipeline() = default;
  virtual void Run(Core::Entities::IEntity*) override;
  virtual void Teardown(Core::Entities::IEntity*) override;

 private:
  ComponentDispatcher dispatcher;
};

}  // namespace Engine::Entities
