#include "draw.h"
#include "snake.h"
#include "apple.h"

void Draw::draw()
{
  // DEBUG: Draw Grid
  if (DEBUG_ENABLED) {
    for (int x = 0; x < SCREEN_WIDTH; x += DEFAULT_BOX_SIZE) {
      DrawLine(x, 0, x, SCREEN_HEIGHT, {255, 255, 255, 40});
    }

    for (int y = 0; y < SCREEN_HEIGHT; y += DEFAULT_BOX_SIZE) {
      DrawLine(0, y, SCREEN_WIDTH, y, {255, 255, 255, 40});
    }
  }

  // Draw Snake
  Snake* snake = state->getSnake();
  for (const auto& segment : snake->body) {
    DrawRectangleRec({segment->position.x, segment->position.y, snake->size, snake->size}, GREEN);
  }

  // Draw Apple
  Apple* apple = state->getApple();

  // DEBUG: Collision
  Vector2 snakeHeadCenter = {
      snake->head->position.x + DEFAULT_BOX_SIZE / 2,
      snake->head->position.y + DEFAULT_BOX_SIZE / 2,
  };
  Vector2 appleCenter = {
      apple->position.x + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
      apple->position.y + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
  };

  if (DEBUG_ENABLED) {
    DrawCircleLinesV(snakeHeadCenter, DEFAULT_BOX_SIZE / 2 - 2, RED);
    DrawCircleLinesV(appleCenter, DEFAULT_BOX_SIZE / 2 - 2, GREEN);
  }
};
