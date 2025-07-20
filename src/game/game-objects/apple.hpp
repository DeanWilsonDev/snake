#pragma once

#include "game/settings/game-settings.h"
#include "core/entity.h"
#include "physics/components/collider-component-2d.hpp"

namespace Game {

struct AppleParams {
  GameSettings& settings;
  Physics::Components::ColliderComponent2D& colliderComponent;
};

class Apple final : public Core::Entity {
 public:
  explicit Apple(const AppleParams& params);
  void Update(float deltaTime) override;
  void Initialize();
  [[nodiscard]] Core::Math::Vector2D GetNewPosition() const;
  [[nodiscard]] Core::Math::Vector2D GetCenter() const;

  [[nodiscard]] Physics::Components::ColliderComponent2D GetColliderComponent() const
  {
    return this->colliderComponent;
  }

  [[nodiscard]] float GetSize() const { return this->size; }

 private:
  GameSettings& settings;
  Physics::Components::ColliderComponent2D& colliderComponent;
  float size = {10};
};
}  // namespace Game
