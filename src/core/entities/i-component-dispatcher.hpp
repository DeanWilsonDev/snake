//
// Created by Dean Wilson 6th June 2026
//

#pragma once

namespace Core {
namespace Entities {
class IEntity;

class IComponentDispatcher {
 public:
  virtual ~IComponentDispatcher() = default;
  virtual void Dispatch(IEntity* entity) = 0;
};

}  // namespace Entities
}  // namespace Core
