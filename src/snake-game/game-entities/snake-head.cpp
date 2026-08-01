#include "snake-head.hpp"
#include "engine/input/components/input-component.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"
#include "snake-game/game-components/snake-body-component.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake-game/game-entities/snake.hpp"
#include "debug/debug.hpp"

namespace SnakeGame {

SnakeHead::SnakeHead(const SnakeHeadParams& params) : SnakeGame::SnakeSegment(params) {}

void SnakeHead::OnRegistration()
{
  SnakeSegment::OnRegistration();
  this->AddComponent<Engine::Input::Components::InputComponent>();
  this->AddComponent<SnakeBodyComponent>();
}

void SnakeHead::BeginPlay()
{
  SnakeSegment::BeginPlay();

  this->inputComponent = this->GetComponent<Engine::Input::Components::InputComponent>();

  this->inputComponent->Bind("Up", [this]() { this->SetDirection({0.0f, -1.0f}); });
  this->inputComponent->Bind("Down", [this]() { this->SetDirection({0.0f, 1.0f}); });
  this->inputComponent->Bind("Left", [this]() { this->SetDirection({-1.0f, 0.0f}); });
  this->inputComponent->Bind("Right", [this]() { this->SetDirection({1.0f, 0.0f}); });
}

void SnakeHead::Update(const float deltaTime)
{
  SnakeSegment::Update(deltaTime);
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
