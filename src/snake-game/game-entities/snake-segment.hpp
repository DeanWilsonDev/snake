#pragma once

#include <memory>
#include "engine/entities/entity.hpp"
#include "core/rendering/components/i-render-component-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/math/i-transform-2d.hpp"

namespace Core::Components {
class TransformComponent2D;
}
namespace Physics::Components {
class ColliderComponent2D;
}
namespace SnakeGame {

struct SnakeSegmentParams : Engine::Entities::EntityParams {
  int index{0};
  Core::Math::ITransform2D& initialTransform;

  SnakeSegmentParams(int index, Core::Math::ITransform2D* transform, bool active = true)
      : Engine::Entities::EntityParams(transform, active)
      , index(index)
      , initialTransform(*transform)
  {
  }
};

class SnakeSegment final : public Engine::Entities::Entity {
 public:
  // Properties
  int index = {0};

  // Constructor
  explicit SnakeSegment(const SnakeSegmentParams& params);
  ~SnakeSegment() override;

  void OnRegistration() override;
  void DebugUpdate() const override;

  [[nodiscard]] Core::Rendering::Components::IRenderComponent2D& GetRendererComponent2D();

  [[nodiscard]] Physics::Collision::Components::ColliderComponent2D& GetColliderComponent();

  [[nodiscard]] const Core::Rendering::Components::IRenderComponent2D&
  GetRendererComponent2D() const;

  [[nodiscard]] const Physics::Collision::Components::ColliderComponent2D&
  GetColliderComponent() const;

  void Move(Core::Math::Vector2D newPosition);
};
}  // namespace SnakeGame
