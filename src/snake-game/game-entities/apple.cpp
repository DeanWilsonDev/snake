#include "apple.hpp"
#include <memory>
#include "core/components/i-collision-component-2d.hpp"
#include "engine/entities/entity.hpp"
#include "core/color/color.hpp"
#include "debug/debug.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "core/math/vector-2d.hpp"
#include "engine/spatial/size-2d.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"
#include "core/rendering/components/i-render-component-2d.hpp"
#include "renderer-2d/components/render-component-2d.hpp"
#include "core/logging/log.hpp"

namespace SnakeGame {

Apple::Apple(const AppleParams& params) : Engine::Entities::Entity(params) {}

void Apple::OnRegistration()
{
  LOG_TRACE("[Apple] Initializing Apple from Constructor");

  this->transformComponent = make_unique<Engine::Spatial::Components::TransformComponent2D>(
      Core::Math::Vector2D::Zero(), 0, Engine::Spatial::Size2D(this->size)
  );

  LOG_TRACE(
      "[Apple] Checking TransformComponent2D is Initialized: [{}]",
      static_cast<void*>(&this->transformComponent)
  );

  this->AddComponent<Renderer2D::Components::RenderComponent2D>(
      *this->transformComponent, Core::Color::Red, this->GetActive()
  );

  LOG_TRACE(
      "[Apple] Checking RenderComponent2D is Initialized: [{}]",
      static_cast<void*>(&*this->GetComponent<Core::Rendering::Components::IRenderComponent2D>())
  );

  const auto appleColliderParams = Physics::Collision::Components::ColliderComponentParams{
      .transform = this->transformComponent.get()
  };

  this->AddComponent<Physics::Collision::Components::ColliderComponent2D>(appleColliderParams);

  LOG_TRACE(
      "[Apple] Checking ColliderComponent2D is Initialized: [{}]",
      static_cast<void*>(&*this->GetComponent<Core::Components::IColliderComponent2D>())
  );

  // MAIN QUEST: This should be handled by the apple spawner
  // this->transformComponent->SetPosition(this->GetNewPosition());
};

void Apple::BeginPlay()
{
  UMBRA_DEBUG({},"Apple Begin Play plays Once");
}

void Apple::OnActivate(){

  UMBRA_DEBUG({},"Apple Active on Load");
  this->SetActive(false);
  UMBRA_DEBUG({},"Apple Deactivated");
  this->SetActive(true);
  UMBRA_DEBUG({},"Apple Reactivated");

}

void Apple::Update([[maybe_unused]] const float deltaTime) {}

void Apple::DebugUpdate() const
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

void Apple::DebugRender() const {}

Physics::Collision::Components::ColliderComponent2D& Apple::GetColliderComponent()
{
  return *this->GetComponent<Physics::Collision::Components::ColliderComponent2D>();
}

Core::Rendering::Components::IRenderComponent2D& Apple::GetRendererComponent2D()
{
  return *this->GetComponent<Core::Rendering::Components::IRenderComponent2D>();
}

const Physics::Collision::Components::ColliderComponent2D& Apple::GetColliderComponent() const
{
  return *this->GetComponent<Physics::Collision::Components::ColliderComponent2D>();
}

const Core::Rendering::Components::IRenderComponent2D& Apple::GetRendererComponent2D() const
{
  return *this->GetComponent<Core::Rendering::Components::IRenderComponent2D>();
}

}  // namespace SnakeGame
