#pragma once

#include <memory>
#include "core/entity/game-entity.hpp"
#include "renderer-2d/components/i-render-component-2d.hpp"
#include "renderer-2d/components/render-component-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/math/i-transform-2d.hpp"

namespace Core::Components {
class TransformComponent2D;
}
namespace Physics::Components {
class ColliderComponent2D;
}
namespace Game {

struct SnakeSegmentParams : Core::Entity::GameEntityParams {
  int index{0};
  Core::Math::ITransform2D& initialTransform;

  SnakeSegmentParams(int index, Core::Math::ITransform2D* transform, bool active = true)
      : Core::Entity::GameEntityParams(transform, active)
      , index(index)
      , initialTransform(*transform)
  {
  }
};

class SnakeSegment final : public Core::Entity::GameEntity {
 public:
  // Properties
  int index = {0};

  // Constructor
  explicit SnakeSegment(const SnakeSegmentParams& params);
  ~SnakeSegment() override;

  void DebugUpdate() override;

  // Getters
  [[nodiscard]] Renderer2D::Component::IRenderComponent2D& GetRendererComponent2D()
  {
    return *this->renderComponent;
  }

  [[nodiscard]] Physics::Collision::Components::ColliderComponent2D& GetColliderComponent() const
  {
    return *this->colliderComponent;
  }

  void Move(Core::Math::Vector2D newPosition);

 private:
  std::unique_ptr<Renderer2D::Component::RenderComponent2D> renderComponent{nullptr};
  std::unique_ptr<Physics::Collision::Components::ColliderComponent2D> colliderComponent{nullptr};
};
}  // namespace Game
