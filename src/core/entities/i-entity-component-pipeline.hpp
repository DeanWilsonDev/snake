//
// Created by Dean Wilson 6th June 2026
//

#pragma once

namespace Core {
namespace Entities {
class IEntity;

class IEntityComponentPipeline {
 public:
  virtual ~IEntityComponentPipeline() = default;
  virtual void Run(IEntity* entity) = 0;
};

}  // namespace Entities
}  // namespace Core
