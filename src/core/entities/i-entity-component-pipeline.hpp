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
  virtual void Run(IEntity* entity) = 0;
  virtual void Teardown(IEntity* entity) = 0;
};

}  // namespace Entities
}  // namespace Core
