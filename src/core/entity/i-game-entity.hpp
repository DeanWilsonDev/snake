//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once

#include "i-entity.hpp"
#include "core/components/transform-component-2d.hpp"

namespace Core::Components {
class IComponent;
}

namespace Core {
namespace Entity {

class IGameEntity : public IEntity {
 public:
  ~IGameEntity() override = 0;

  virtual void Update(float deltaTime) override = 0;
  virtual void DebugUpdate() override = 0;
  virtual void Initialize() override = 0;
  virtual Components::TransformComponent2D& GetTransformComponent() = 0;
};
}  // namespace Entity
}  // namespace Core
