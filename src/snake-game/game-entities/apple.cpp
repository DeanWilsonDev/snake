#include "apple.hpp"
#include <memory>
#include "core/entity/game-entity.hpp"
#include "core/color/color.hpp"
#include "debug/debug.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "core/core.hpp"
#include "core/math/size-2d.hpp"
#include "core/components/transform-component-2d.hpp"
#include "core/rendering/components/i-render-component-2d.hpp"
#include "renderer-2d/components/render-component-2d.hpp"
#include "core/logging/log.hpp"

namespace SnakeGame {

Apple::Apple(const AppleParams& params) : Core::Entity::GameEntity(params) {}

void Apple::Initialize()
{
  GameEntity::Initialize();

  LOG_TRACE("[Apple] Initializing Apple from Constructor");

  this->transformComponent = make_unique<Core::Components::TransformComponent2D>(
      this->GetNewPosition(), 0, Core::Math::Size2D(this->size)
  );

  LOG_TRACE(
      "[Apple] Checking TransformComponent2D is Initialized: [{}]",
      static_cast<void*>(&this->transformComponent)
  );

  // SIDE QUEST: Ideally, the Game should just be able to call a factory to get a IRenderComponent2D
  // and have the factory determine which component we are using
  this->renderComponent = make_unique<Renderer2D::Components::RenderComponent2D>(
      *this->transformComponent, Core::Color::Red, this->GetActive()
  );

  LOG_TRACE(
      "[Apple] Checking RenderComponent2D is Initialized: [{}]",
      static_cast<void*>(&this->renderComponent)
  );

  const auto appleColliderParams = Physics::Collision::Components::ColliderComponentParams{
      .transform = this->transformComponent.get()
  };

  this->colliderComponent =
      make_unique<Physics::Collision::Components::ColliderComponent2D>(appleColliderParams);

  LOG_TRACE(
      "[Apple] Checking ColliderComponent2D is Initialized: [{}]",
      static_cast<void*>(&this->colliderComponent)
  );

  this->transformComponent->SetPosition(this->GetNewPosition());
};

void Apple::Update([[maybe_unused]] const float deltaTime) {}

void Apple::DebugUpdate()
{
  UMBRA_DEBUG(this->transformComponent->GetPosition().x, "Apple/Position/X");
  UMBRA_DEBUG(this->transformComponent->GetPosition().y, "Apple/Position/Y");
  UMBRA_DEBUG(this->transformComponent->GetScale().GetWidth(), "Apple/Scale/Width");
  UMBRA_DEBUG(this->transformComponent->GetScale().GetHeight(), "Apple/Scale/Height");
  UMBRA_DEBUG(this->GetSize(), "Apple/Size");
  UMBRA_DEBUG(this->GetActive(), "Apple/Active");

  UMBRA_DEBUG(this->GetColliderComponent().GetCollider().GetWorldRect().x, "Apple/Collision/X");
  UMBRA_DEBUG(this->GetColliderComponent().GetCollider().GetWorldRect().y, "Apple/Collision/Y");
  UMBRA_DEBUG(
      this->GetColliderComponent().GetCollider().GetWorldRect().width, "Apple/Collision/width"
  );
  UMBRA_DEBUG(
      this->GetColliderComponent().GetCollider().GetWorldRect().height, "Apple/Collision/height"
  );
}


Physics::Collision::Components::ColliderComponent2D& Apple::GetColliderComponent() const
{
  return *this->colliderComponent;
}

Core::Rendering::Components::IRenderComponent2D& Apple::GetRendererComponent2D() const
{
  return *this->renderComponent;
}

}  // namespace SnakeGame
