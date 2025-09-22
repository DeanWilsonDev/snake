#pragma once

#include "core/components/transform-component-2d.hpp"
#include "core/entity/game-entity.hpp"
#include "core/math/transform-2d.hpp"
#include "core/math/geometry/rectangle.h"
#include "renderer-2d/components/render-component-2d.h"

namespace Core::Components {
class TransformComponent2D;
}
namespace Physics::Components {
class ColliderComponent2D;
}
namespace Game {

struct SnakeSegmentParams {
  int index;
  Core::Math::ITransform2D* transform;
  Physics::Components::ColliderComponent2D* colliderComponent;
  Renderer2D::Component::RenderComponent2D* renderComponent;
};

class SnakeSegment final : public Core::Entity::GameEntity {
 public:
  // Properties
  int index = {0};

  // Constructor
  explicit SnakeSegment(const SnakeSegmentParams& props);
  ~SnakeSegment() override;

  // Getters
  [[nodiscard]] Renderer2D::Component::IRenderComponent2D* GetRendererComponent2D() const
  {
    return this->renderComponent;
  }

  [[nodiscard]] Physics::Components::ColliderComponent2D* GetColliderComponent() const
  {
    return this->colliderComponent;
  }

  // Methods
  SnakeSegment* InitializeSnakeSegment(int index, Core::Math::ITransform2D& transform);

  void Move(Core::Math::Vector2D newPosition);

 private:
  Renderer2D::Component::RenderComponent2D* renderComponent{nullptr};
  Physics::Components::ColliderComponent2D* colliderComponent{nullptr};
  Core::Math::Geometry::Rectangle* bounds{nullptr};
};
}  // namespace Game
