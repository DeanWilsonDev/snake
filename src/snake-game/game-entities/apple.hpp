#pragma once

#include <memory>
#include "core/spatial/i-transform-2d.hpp"
#include "engine/entities/entity.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/rendering/components/i-render-component-2d.hpp"

namespace Core {
namespace Rendering {
namespace Component {
class IRenderComponent2D;
}
}  // namespace Rendering
}  // namespace Core

namespace SnakeGame {

struct AppleParams : Engine::Entities::EntityParams {
  Core::Spatial::ITransform2D* transform{nullptr};

  AppleParams(Core::Spatial::ITransform2D* transform = nullptr, bool active = true)
      : Engine::Entities::EntityParams(transform, active)
  {
  }
};

class Apple final : public Engine::Entities::Entity {
 public:
  explicit Apple(const AppleParams& params);
  void BeginPlay() override;
  void OnActivate() override;
  void Update(float deltaTime) override;
  void DebugUpdate() const override;
  void DebugRender() const override;
  void OnRegistration() override;

  [[nodiscard]] Physics::Collision::Components::ColliderComponent2D& GetColliderComponent();
  [[nodiscard]] Core::Rendering::Components::IRenderComponent2D& GetRendererComponent2D();
  [[nodiscard]] const Physics::Collision::Components::ColliderComponent2D&
  GetColliderComponent() const;
  [[nodiscard]] const Core::Rendering::Components::IRenderComponent2D&
  GetRendererComponent2D() const;

  [[nodiscard]] float GetSize() const { return this->size; }

 private:
  // unique_ptr<Physics::Collision::Components::ColliderComponent2D> colliderComponent{nullptr};
  // unique_ptr<Core::Rendering::Components::IRenderComponent2D> renderComponent{nullptr};
  float size = {10};
};
}  // namespace SnakeGame
