#pragma once

#include "engine/entities/entity.hpp"
#include "core/rendering/components/i-render-component-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/spatial/i-transform-2d.hpp"

namespace Core::Components {
class TransformComponent2D;
}
namespace Physics::Components {
class ColliderComponent2D;
}
namespace SnakeGame {

struct SnakeSegmentParams : Engine::Entities::EntityParams {
  const int index{0};
  const Core::Spatial::ITransform2D& transform;

  SnakeSegmentParams(
      const int index, const Core::Spatial::ITransform2D& transform, const bool active = true
  )
      : Engine::Entities::EntityParams(transform, active), index(index), transform(transform)
  {
  }
};

class SnakeSegment : public Engine::Entities::Entity {
 public:
  // Properties
  int index = {0};

  // Constructor
  explicit SnakeSegment(const SnakeSegmentParams& params);
  ~SnakeSegment() override;

  virtual void OnRegistration() override;
  virtual void BeginPlay() override;
  void Update(const float deltaTime) override;
  void DebugUpdate() const override;

  [[nodiscard]] Core::Rendering::Components::IRenderComponent2D& GetRendererComponent2D();

  [[nodiscard]] Physics::Collision::Components::ColliderComponent2D& GetColliderComponent();

  [[nodiscard]] const Core::Rendering::Components::IRenderComponent2D&
  GetRendererComponent2D() const;

  [[nodiscard]] const Physics::Collision::Components::ColliderComponent2D&
  GetColliderComponent() const;

  void Step();
  void SetDirection(Core::Math::Vector2D value);

 protected:
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
  float size = {0};
  Core::Math::Vector2D direction{};
  Core::Math::Vector2D pendingDirection{};
  float speed = 10.0f;
  float moveTimer = 0.0f;
  float moveInterval = 0.2f;
};
}  // namespace SnakeGame
