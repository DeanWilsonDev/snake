#include "apple.hpp"
#include <memory>
#include "core/entity/game-entity.hpp"
#include "core/color.hpp"
#include "debug/debug.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "core/core.hpp"
#include "core/math/size-2d.hpp"
#include "core/components/transform-component-2d.hpp"
#include "core/components/i-render-component-2d.hpp"
#include "renderer-2d/components/render-component-2d.hpp"
#include "umbra/log.h"

namespace Game {

Apple::Apple(const AppleParams& params)
    : Core::Entity::GameEntity(params), settings(params.settings)
{
  LOG_TRACE("[Apple] Initializing Apple from Constructor");

  this->transformComponent = make_unique<Core::Components::TransformComponent2D>(
      this->GetNewPosition(), 0, Core::Math::Size2D(this->size)
  );

  LOG_TRACE(
      "[Apple] Checking TransformComponent2D is Initialized: [{}]",
      static_cast<void*>(&this->transformComponent)
  );

  // SIDE QUEST: Ideally, the Game should just be able to call a factory to get a IRenderComponent2D and have the factory determine which component we are using
  this->renderComponent = make_unique<Renderer2D::Components::RenderComponent2D>(
      *this->transformComponent, Core::COLOR_RED, this->GetActive()
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
}

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

void Apple::Initialize()
{
  GameEntity::Initialize();
  this->transformComponent->SetPosition(this->GetNewPosition());
};

Core::Math::Vector2D Apple::GetNewPosition() const
{
  const auto boxSize = static_cast<float>(this->settings.GetBoxSize());
  const auto screenWidth = static_cast<float>(this->settings.GetScreenWidth());
  const auto screenHeight = static_cast<float>(this->settings.GetScreenHeight());

  const auto maxWidth = static_cast<int>(screenWidth / boxSize - 1.f);
  const auto maxHeight = static_cast<int>(screenHeight / boxSize - 1.f);

  const auto posX = static_cast<float>(Core::GetRandomValue(0, maxWidth)) * boxSize +
                    (boxSize - boxSize / 2.0f) / 2.0f;

  const auto posY = static_cast<float>(Core::GetRandomValue(0, maxHeight)) * boxSize +
                    (boxSize - boxSize / 2.0f) / 2.0f;

  return {posX, posY};
}

Core::Math::Vector2D Apple::GetCenter() const
{
  const auto boxSize = static_cast<float>(this->settings.GetBoxSize());
  return {
      this->transformComponent->position.x + (boxSize - boxSize / 2.0f) / 2.0f,
      this->transformComponent->position.y + (boxSize - boxSize / 2.0f) / 2.0f,
  };
}

Physics::Collision::Components::ColliderComponent2D& Apple::GetColliderComponent() const
{
  return *this->colliderComponent;
}

Core::Components::IRenderComponent2D& Apple::GetRendererComponent2D() const
{
  return *this->renderComponent;
}

}  // namespace Game
