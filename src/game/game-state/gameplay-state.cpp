
#include "gameplay-state.hpp"
#include "game/settings/game-settings.h"
#include "gameplay-state-machine.h"
#include "game/snake.hpp"
#include "game/apple.hpp"
#include "physics/components/collider-component-2d.hpp"

#include <assert.h>

namespace Renderer2D {
class IRenderer;
}

namespace Game {

GameplayState::GameplayState(GameplayStateMachine* stateMachine)
    : gameplayStateMachine(stateMachine)
{
}

void GameplayState::Enter()
{
  LOG_TRACE("[GameplayState] Beginning New Game");
  this->gameplayStateMachine->InitializeSnake();
  this->gameplayStateMachine->InitializeApple();
}

void GameplayState::Update(float deltaTime)
{
  Snake* snake = this->gameplayStateMachine->GetSnake();
  Apple* apple = this->gameplayStateMachine->GetApple();
  assert(snake);
  assert(apple);

  // Main Quest: [GameplayState] Move collider to SnakeSegment so the head can collide with the apple and other segments
  if (snake->GetColliderComponent().Intersects(apple->GetColliderComponent())) {
    apple->transform.position = apple->GetNewPosition();
    this->gameplayStateMachine->IncreaseScore();
    snake->SetGrow(true);
  }


  for (int i = 0; i < snake->body.size(); i++) {
    this->debugEnabled&& std::cout << "Body[" << i << "]: " << snake->body[i] << std::endl;
    this->debugEnabled&& std::cout << "Body[" << i << "]: " << snake->body[i] << std::endl;

    if (snake->head != nullptr && snake->body[i] != snake->head) {

      // Side Quest: [Debug] Create a Debug module to allow for Debug drawing
      if (this->debugEnabled) {
        DrawRectangleRec(snake->body[i]->GetBounds(), RED);
      }

      if (CheckCollisionRecs(snake->head->GetBounds(), snake->body[i]->GetBounds())) {
        LOG_INFO("Head hit body part with index: {}", i);
        this->session->setState(STATE_GAME_OVER);
      }
    }
  }
}


// Main Quest: [GameplayState] Clean draw function.

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
