//
// Created by Dean Wilson 6th June 2026
//

#pragma once

#include <memory>

namespace Core::Entities {
class IEntity;
}

namespace Core::Entities {
class IComponentRegistrar;
}

namespace Core::Entities {

class IComponentDispatcher {
 public:
  virtual ~IComponentDispatcher() = default;
  virtual void Dispatch(IEntity* entity) = 0;
  virtual void Teardown(IEntity* entity) = 0;
  virtual void AddRegistrar(std::unique_ptr<Core::Entities::IComponentRegistrar> registrar) = 0;
};

}  // namespace Core::Entities
