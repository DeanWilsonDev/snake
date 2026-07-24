#include "snake-head.hpp"
#include "engine/input/components/input-component.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake-game/game-entities/snake.hpp"

namespace SnakeGame {

SnakeHead::SnakeHead(const SnakeHeadParams& params) : SnakeGame::SnakeSegment(params) {}

void SnakeHead::OnRegistration()
{
  SnakeSegment::OnRegistration();
  this->AddComponent<Engine::Input::Components::InputComponent>();
}

void SnakeHead::BeginPlay()
{
  auto* inputComponent = this->GetComponent<Engine::Input::Components::InputComponent>();
  inputComponent->BindAxis("MoveHorizontal", [this](Core::Input::ActionValue value) {
    this->direction.x = std::get<float>(value);
  });
  inputComponent->BindAxis("MoveVertical", [this](Core::Input::ActionValue value) {
    this->direction.y = std::get<float>(value);
  });
}

}  // namespace SnakeGame
