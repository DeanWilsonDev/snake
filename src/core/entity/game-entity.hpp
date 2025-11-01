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

struct GameEntityParams : EntityParams {
  Components::TransformComponent2D* transform = {nullptr};
};

class GameEntity : public Entity {
 public:
  explicit GameEntity(const GameEntityParams& params);

  GameEntity(const GameEntity& other)
      : Entity({.active = other.IsActive()}), transform(other.transform)
  {
  }

  ~GameEntity() override;

  GameEntity& operator=(const GameEntity& other)
  {
    if (this != &other) {
      this->transform = other.transform;
    }
    return *this;
  }

  void Update(float deltaTime) override;
  void Initialize() override;

  // Properties
  Components::TransformComponent2D* transform{nullptr};
};
}  // namespace Core::Entity
