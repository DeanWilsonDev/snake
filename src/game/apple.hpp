#pragma once

#include "settings/game-settings.h"
#include "core/entity.h"
#include "physics/components/collider-component-2d.hpp"

namespace Game {

struct AppleParams {
  GameSettings& settings;
  Physics::Components::ColliderComponent2D& colliderComponent;
};

class Apple final : public UserInterface::Entity {
 public:
  explicit Apple(const AppleParams& params);
  void Update(float deltaTime) override;
  void Initialize();
  [[nodiscard]] UserInterface::Math::Vector2D GetNewPosition() const;
  [[nodiscard]] UserInterface::Math::Vector2D GetCenter() const;

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
