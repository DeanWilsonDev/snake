#pragma once

#include "game/settings/game-settings.h"
#include "core/entity/game-entity.hpp"
#include "physics/components/collider-component-2d.hpp"

namespace Renderer2D::Component {
class RenderComponent2D;
}

namespace Game {

struct AppleParams: Core::Entity::GameEntityParams {
  GameSettings& settings;
};

class Apple final : public Core::Entity::GameEntity {
 public:
  explicit Apple(const AppleParams& params);
  void Update(float deltaTime) override;
  void Initialize() override;
  [[nodiscard]] Core::Math::Vector2D GetNewPosition() const;
  [[nodiscard]] Core::Math::Vector2D GetCenter() const;

  [[nodiscard]] Physics::Components::ColliderComponent2D* GetColliderComponent() const;
  [[nodiscard]] Renderer2D::Component::RenderComponent2D* GetRendererComponent2D() const;

  [[nodiscard]] float GetSize() const { return this->size; }

 private:
  GameSettings& settings;
  Physics::Components::ColliderComponent2D* colliderComponent = {nullptr};
  Renderer2D::Component::RenderComponent2D* renderComponent = {nullptr};
  float size = {10};
};
}  // namespace Game
