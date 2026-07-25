#include "snake-head.hpp"
#include "engine/input/components/input-component.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake-game/game-entities/snake.hpp"
#include "debug/debug.hpp"

namespace SnakeGame {

SnakeHead::SnakeHead(const SnakeHeadParams& params) : SnakeGame::SnakeSegment(params) {}

void SnakeHead::OnRegistration()
{
  SnakeSegment::OnRegistration();
  this->AddComponent<Engine::Input::Components::InputComponent>();
}

void SnakeHead::BeginPlay()
{
  this->inputComponent = this->GetComponent<Engine::Input::Components::InputComponent>();

  this->inputComponent->BindAxis("MoveHorizontal", [this](Core::Input::ActionValue value) {
    Core::Math::Vector2D newDirection = {
        std::roundf(
            (this->transform->GetPosition().x + std::get<float>(value) * this->size) / this->size
        ) * this->size,
        std::roundf(
            (this->transform->GetPosition().y + std::get<float>(value) * this->size) / this->size
        ) * this->size
    };

    this->SetDirection(newDirection);
  });

  this->inputComponent->BindAxis("MoveVertical", [this](Core::Input::ActionValue value) {
    Core::Math::Vector2D newDirection = {
        std::roundf(
            (this->transform->GetPosition().x + std::get<float>(value) * this->size) / this->size
        ) * this->size,
        std::roundf(
            (this->transform->GetPosition().y + std::get<float>(value) * this->size) / this->size
        ) * this->size
    };

    this->SetDirection(newDirection);
  });
}

void SnakeHead::Update(const float deltaTime)
{
  this->accumulatedDistance += this->speed * deltaTime;
}

void SnakeHead::DebugUpdate() const
{
  UMBRA_DEBUG(this->GetActive(), "Snake/Head/Active");
  SnakeSegment::DebugUpdate();
}

void SnakeHead::SetDirection(Core::Math::Vector2D desiredDirection)
{
  SnakeSegment::SetDirection(desiredDirection);
  //   if (desiredDirection.x == -this->direction.x && desiredDirection.y == -this->direction.y) {
  //     return;
  //   }
  //   this->direction = desiredDirection;
}

}  // namespace SnakeGame
