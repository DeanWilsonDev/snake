#pragma once

#include "game/settings/game-settings.h"
#include "core/entity/game-entity.hpp"
#include "physics/components/collider-component-2d.hpp"
#include "renderer-2d/components/i-render-component-2d.h"

namespace Game {

struct AppleParams {
  GameSettings& settings;
  Physics::Components::ColliderComponent2D& colliderComponent;
  Renderer2D::Component::IRenderComponent2D& renderComponent;
  Core::Math::Transform2D& transform;
};

class Apple final : public Core::Entity::GameEntity {
 public:
  explicit Apple(const AppleParams& params);
  void Update(float deltaTime) override;
  void Initialize() override;
  [[nodiscard]] Core::Math::Vector2D GetNewPosition() const;
  [[nodiscard]] Core::Math::Vector2D GetCenter() const;

  [[nodiscard]] Physics::Components::ColliderComponent2D GetColliderComponent() const
  {
    return this->colliderComponent;
  }

  [[nodiscard]] Renderer2D::Component::IRenderComponent2D& GetRendererComponent2D() const
  {
    return this->renderComponent;
  }

  [[nodiscard]] float GetSize() const { return this->size; }

 private:
  GameSettings& settings;
  Physics::Components::ColliderComponent2D& colliderComponent;
  Renderer2D::Component::IRenderComponent2D& renderComponent;
  float size = {10};
};
}  // namespace Game
