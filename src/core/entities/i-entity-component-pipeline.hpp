//
// Created by Dean Wilson 6th June 2026
//

#pragma once

#include "core/life-cycle-hooks/i-on-updatable.hpp"
namespace Core {
namespace Entities {
class IEntity;

class IEntityComponentPipeline : public Core::IOnUpdatable {
 public:
  virtual ~IEntityComponentPipeline() = default;
  virtual void Run() = 0;
  virtual void Teardown() = 0;
  virtual void SetEntity(Core::Entities::IEntity* entity) = 0;
};

}  // namespace Entities
}  // namespace Core
