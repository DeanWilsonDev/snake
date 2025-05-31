
#include "gameplay-state.hpp"
#include "../../game/game-settings.h"

namespace Renderer2D {
class IRenderer;
}

namespace Game {

GameplayState::GameplayState(GameplayStateMachine* stateMachine)
    : stateMachine(stateMachine)
{
}
void GameplayState::Enter() {}

void GameplayState::Update(float deltaTime) {}

void GameplayState::Draw(Renderer2D::IRenderer& renderer)
{
  /// The Following is the gameplay states render function

  // DEBUG: Draw Grid
  if (DEBUG_ENABLED) {
    for (int x = 0; x < settings.windowWidth; x += DEFAULT_BOX_SIZE) {
      renderer.DrawLine(x, 0, x, settings.windowHeight, {255, 255, 255, 40});
    }

    for (int y = 0; y < settings.windowHeight; y += DEFAULT_BOX_SIZE) {
      renderer.DrawLine(0, y, settings.windowWidth, y, {255, 255, 255, 40});
    }
  }

  // Draw Snake
  Snake* snake = this->session->getSnake();
  for (const auto& segment : snake->body) {
    DrawRectangleRec({segment->position.x, segment->position.y, snake->size, snake->size}, GREEN);
  }

  // Draw Apple
  Apple* apple = this->session->getApple();

  // DEBUG: Collision
  Vector2 snakeHeadCenter = {
      snake->head->position.x + snake->size / 2,
      snake->head->position.y + snake->size / 2,
  };
  Vector2 appleCenter = {
      apple->position.x + (apple->size - apple->size / 2) / 2.0f,
      apple->position.y + (apple->size - apple->size / 2) / 2.0f,
  };

  if (DEBUG_ENABLED) {
    DrawCircleLinesV(snakeHeadCenter, snake->size / 2 - 2, RED);
    DrawCircleLinesV(appleCenter, apple->size / 2 - 2, GREEN);
  }
}

void GameplayState::Exit() {}
}  // namespace Game
