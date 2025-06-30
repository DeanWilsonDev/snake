#pragma once

#include "settings/game-settings.h"
#include "core/entity.h"
#include "physics/components/collider-component-2d.hpp"

namespace Game {

struct AppleParams {
  GameSettings settings;
  Physics::Components::ColliderComponent2D colliderComponent;
};

class Apple final : public Core::Entity {
 public:
  explicit Apple(const AppleParams& params);
  void Update(float deltaTime) override;
  void Initialize();
  Core::Math::Vector2D GetNewPosition() const;
  Core::Math::Vector2D GetCenter() const;

  Physics::Components::ColliderComponent2D GetColliderComponent() const
  {
    return this->colliderComponent;
  }

  float GetSize() const { return this->size; }

 private:
  GameSettings settings;
  Physics::Components::ColliderComponent2D colliderComponent;
  float size;
};
}  // namespace Game
