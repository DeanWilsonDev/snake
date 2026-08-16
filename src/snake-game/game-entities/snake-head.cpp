#include "snake-head.hpp"
#include "engine/input/components/input-component.hpp"
#include "snake-game/game-components/movement-component.hpp"
#include "snake-game/game-components/snake-body-component.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake-game/game-entities/snake.hpp"
#include "debug/debug.hpp"
#include "core/logging/log.hpp"

namespace SnakeGame {

SnakeHead::SnakeHead(const SnakeHeadParams& params) : SnakeGame::SnakeSegment(params) {}

void SnakeHead::OnRegistration()
{
  SnakeSegment::OnRegistration();
  this->inputComponent = this->AddComponent<Engine::Input::Components::InputComponent>();
  this->AddComponent<SnakeBodyComponent>();

  auto movementParams = MovementComponentParams{.cellSize = this->size};

  this->movementComponent =
      this->AddComponent<MovementComponent>(this->inputComponent, this->transform, movementParams);
}

void SnakeHead::BeginPlay()
{
  SnakeSegment::BeginPlay();
}

void SnakeHead::Update(const float deltaTime)
{
  SnakeSegment::Update(deltaTime);
}

void SnakeHead::DebugUpdate() const
{
  UMBRA_DEBUG(this->GetActive(), "Snake/Head/Active");
  UMBRA_DEBUG(this->transform->position.x, "Snake/Head/Transform/X");
  UMBRA_DEBUG(this->transform->position.y, "Snake/Head/Transform/Y");
  // SnakeSegment::DebugUpdate();
}

}  // namespace SnakeGame
