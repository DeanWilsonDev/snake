#include "movement-component.hpp"
#include "debug/debug.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"
#include "engine/input/components/input-component.hpp"
#include "core/logging/log.hpp"

namespace SnakeGame {

MovementComponent::MovementComponent(
    Engine::Input::Components::InputComponent* inputComponent,
    Engine::Spatial::Components::TransformComponent2D* transform, MovementComponentParams params
)
    : inputComponent(inputComponent)
    , transform(transform)
    , speed(params.speed)
    , moveTimer(params.moveTimer)
    , moveInterval(params.moveInterval)
    , cellSize(params.cellSize) {};

void MovementComponent::BeginPlay()
{
  this->inputComponent->Bind("Up", [this]() {
    LOG_DEBUG("[MovementComponent] UP!");
    this->SetDirection({0.0f, -1.0f});
  });
  this->inputComponent->Bind("Down", [this]() { this->SetDirection({0.0f, 1.0f}); });
  this->inputComponent->Bind("Left", [this]() { this->SetDirection({-1.0f, 0.0f}); });
  this->inputComponent->Bind("Right", [this]() { this->SetDirection({1.0f, 0.0f}); });
}

void MovementComponent::Update(const float)
{
  Step();
}

void MovementComponent::DebugUpdate() const
{
  UMBRA_DEBUG(this->pendingDirection.x, "MovementComponent/Direction/X");
  UMBRA_DEBUG(this->pendingDirection.y, "MovementComponent/Direction/Y");
}

void MovementComponent::SetDirection(Core::Math::Vector2D direction)
{
  this->pendingDirection = direction;
  LOG_DEBUG("[MovementComponent] direction set to {}, {}", direction.x, direction.y);
}

void MovementComponent::Step()
{
  if (this->pendingDirection.x != 0.0f || this->pendingDirection.y != 0.0f) {
    bool isReversal = this->pendingDirection.x == -this->direction.x &&
                      this->pendingDirection.y == -this->direction.y;
    if (!isReversal) {
      this->direction = this->pendingDirection;
    }
  }
  this->transform->GetPosition().x += this->direction.x * this->cellSize;
  this->transform->GetPosition().y += this->direction.y * this->cellSize;
}
}  // namespace SnakeGame
