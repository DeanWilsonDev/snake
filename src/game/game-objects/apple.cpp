#include "apple.hpp"
#include "core/entity/game-entity.hpp"
#include "core/entity/entity.h"
#include "core/color.h"
#include "physics/components/collider-component-2d.hpp"
#include "core/math/vector-2d.hpp"
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
}

void Apple::Update([[maybe_unused]] const float deltaTime) {}

void Apple::Initialize()
{
  GameEntity::Initialize();
  this->transform->position = this->GetNewPosition();
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
