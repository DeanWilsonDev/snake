#include "apple.hpp"

#include "core/core.h"
#include "core/components/transform-component-2d.hpp"
#include "renderer-2d/components/render-component-2d.h"

namespace Game {

Apple::Apple(const AppleParams& params) : GameEntity(params), settings(params.settings)
{
  this->renderComponent = new Renderer2D::Component::RenderComponent2D(
      *this->transform, Core::COLOR_RED, this->Entity::GetActive()
  );

  const auto appleColliderParams =
      Physics::Components::ColliderComponentParams{.transform = *this->transform};
  this->colliderComponent = new Physics::Components::ColliderComponent2D(appleColliderParams);

  LOG_DEBUG(
      "[Apple] Checking RenderComponent is Initialized: [{}]",
      static_cast<void*>(&this->renderComponent)
  );
  LOG_DEBUG(
      "[Apple] Checking ColliderComponent is Initialized: [{}]",
      static_cast<void*>(&this->colliderComponent)
  );
  LOG_DEBUG(
      "[Apple] Checking GameSettings is Initialized: [{}]", static_cast<void*>(&this->settings)
  );
}

void Apple::Update([[maybe_unused]] const float deltaTime)
{
  LOG_DEBUG(
      "[Apple] position changed to: ({}, {}) - Address ({})",
      this->transform->position.x,
      this->transform->position.y,
      static_cast<void*>(&(this->transform->position))
  );
}

void Apple::Initialize()
{
  GameEntity::Initialize();
  LOG_TRACE("[Apple] Initializing");
  this->transform->position = this->GetNewPosition();
  LOG_DEBUG(
      "[Apple] position changed to: ({}, {}) - Address ({})",
      this->transform->position.x,
      this->transform->position.y,
      static_cast<void*>(&(this->transform->position))
  );

  LOG_TRACE("[Apple] Finished Initializing");
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
      this->transform->position.x + (boxSize - boxSize / 2.0f) / 2.0f,
      this->transform->position.y + (boxSize - boxSize / 2.0f) / 2.0f,
  };
}

Physics::Components::ColliderComponent2D* Apple::GetColliderComponent() const
{
  return this->colliderComponent;
}

Renderer2D::Component::RenderComponent2D* Apple::GetRendererComponent2D() const
{
  return this->renderComponent;
}

}  // namespace Game
