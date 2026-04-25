#pragma once

#include <memory>
#include "core/math/i-transform-2d.hpp"
#include "game/settings/snake-game-settings.hpp"
#include "core/entity/game-entity.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "core/rendering/components/i-render-component-2d.hpp"

namespace Core {
namespace Rendering {
namespace Component {
class IRenderComponent2D;
}
}  // namespace Rendering
}  // namespace Core

namespace SnakeGame {

struct AppleParams : Core::Entity::GameEntityParams {
  SnakeGameSettings& settings;

  AppleParams(
      SnakeGameSettings& settings, Core::Math::ITransform2D* transform = nullptr, bool active = true
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
  [[nodiscard]] Core::Rendering::Components::IRenderComponent2D& GetRendererComponent2D() const;

  [[nodiscard]] float GetSize() const { return this->size; }

 private:
  SnakeGameSettings& settings;
  unique_ptr<Physics::Collision::Components::ColliderComponent2D> colliderComponent{nullptr};
  unique_ptr<Core::Rendering::Components::IRenderComponent2D> renderComponent{nullptr};
  float size = {10};
};
}  // namespace Game
