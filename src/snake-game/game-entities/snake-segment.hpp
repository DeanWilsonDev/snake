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

 protected:
  // MAIN QUEST: Set this to the box size in settings
  float size = {20.0f};
};
}  // namespace SnakeGame
