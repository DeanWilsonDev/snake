//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "entity.h"
#include "core/components/transform-component-2d.hpp"

namespace Core::Components {
class IComponent;
}
namespace Core::Math {
struct Transform2D;
}

namespace Core::Entity {

class GameEntity : public Entity {
 public:
  explicit GameEntity(Components::TransformComponent2D& transform);

  void Update(float deltaTime) override;
  void Initialize() override;

  // Properties
  Components::TransformComponent2D* transform;

};
}  // namespace Core::Entity
