//
// Created by Dean Wilson 8th July 2026
//

#pragma once

#include <memory>
#include "core/systems/i-system.hpp"

namespace Core::Entities {
class IEntity;
}

namespace Core::Debug {
class IOnDebugable;
}

namespace Core {
class IOnUpdatable;
}

namespace Core::Entities {
class IEntityManager : public Core::Systems::ISystem {
 public:
  virtual ~IEntityManager() = default;
  virtual Core::Entities::IEntity* AddEntity(std::unique_ptr<Core::Entities::IEntity> entity) = 0;
  virtual void RemoveEntity(Core::Entities::IEntity* entity) = 0;
};

}  // namespace Core::Entities
