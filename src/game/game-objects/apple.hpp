#pragma once

#include <memory>
#include "core/math/i-transform-2d.hpp"
#include "game/settings/game-settings.hpp"
#include "core/entity/game-entity.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "core/components/i-render-component-2d.hpp"

namespace Core::Component {
class IRenderComponent2D;
}

namespace Game {

struct AppleParams : Core::Entity::GameEntityParams {
  GameSettings& settings;

  AppleParams(
      GameSettings& settings, Core::Math::ITransform2D* transform = nullptr, bool active = true
  )
      : Core::Entity::GameEntityParams(transform, active), settings(settings)
  {
  }
};

class Apple final : public Core::Entity::GameEntity {
 public:
  explicit Apple(const AppleParams& params);
  void Update(float deltaTime) override;
  void DebugUpdate() override;
  void Initialize() override;
  [[nodiscard]] Core::Math::Vector2D GetNewPosition() const;
  [[nodiscard]] Core::Math::Vector2D GetCenter() const;

  [[nodiscard]] Physics::Collision::Components::ColliderComponent2D& GetColliderComponent() const;
  [[nodiscard]] Core::Components::IRenderComponent2D& GetRendererComponent2D() const;

  [[nodiscard]] float GetSize() const { return this->size; }

 private:
  GameSettings& settings;
  unique_ptr<Physics::Collision::Components::ColliderComponent2D> colliderComponent{nullptr};
  unique_ptr<Core::Components::IRenderComponent2D> renderComponent{nullptr};
  float size = {10};
};
}  // namespace Game
