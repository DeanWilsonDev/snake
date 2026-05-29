#pragma once

#include <memory>
#include "engine/entity/game-entity.hpp"
#include "core/rendering/components/i-render-component-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/math/i-transform-2d.hpp"
#include "core/components/transform-component-2d.hpp"

namespace Core::Components {
class TransformComponent2D;
}
namespace Physics::Components {
class ColliderComponent2D;
}
namespace SnakeGame {

struct SnakeSegmentParams : Engine::Entity::GameEntityParams {
  int index{0};
  Core::Math::ITransform2D& initialTransform;

  SnakeSegmentParams(int index, Core::Math::ITransform2D* transform, bool active = true)
      : Engine::Entity::GameEntityParams(transform, active)
      , index(index)
      , initialTransform(*transform)
  {
  }
};

class SnakeSegment final : public Engine::Entity::GameEntity {
 public:
  // Properties
  int index = {0};

  // Constructor
  explicit SnakeSegment(const SnakeSegmentParams& params);
  ~SnakeSegment() override;

  void DebugUpdate() const override;
  void DebugRender() const override;
  virtual void Update(float deltaTime) override;
  virtual void Initialize() override;

  [[nodiscard]] Core::Rendering::Components::IRenderComponent2D& GetRendererComponent2D()
  {
    return *this->renderComponent;
  }

  [[nodiscard]] Physics::Collision::Components::ColliderComponent2D& GetColliderComponent() const
  {
    return *this->colliderComponent;
  }

  void Move(Core::Math::Vector2D newPosition);

 private:
  std::unique_ptr<Core::Rendering::Components::IRenderComponent2D> renderComponent{nullptr};
  // 1UP: Add an interface in Core for this
  std::unique_ptr<Physics::Collision::Components::ColliderComponent2D> colliderComponent{nullptr};
};
}  // namespace SnakeGame
