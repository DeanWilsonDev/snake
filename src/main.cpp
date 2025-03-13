#include "raylib.h"
#include <cmath>
#include <deque>
#include <iostream>
#include <string>

#define SCREEN_WIDTH (500)
#define SCREEN_HEIGHT (500)
#define DEFAULT_TARGET_FPS (60)
#define DEFAULT_BOX_SIZE (20.0f)
#define DEBUG_ENABLED true

#define WINDOW_TITLE "Snake"

struct Apple {
  Vector2 position;
  float size;
};

struct Snake {
  float size;
  float speed;
  int length;
  Vector2 direction;
  Vector2 position;
  std::deque<Vector2> body;
  bool grow;
};

struct GameState {
  int score;
};

static const Snake DefaultSnake = {
    .size = DEFAULT_BOX_SIZE,
    .speed = DEFAULT_BOX_SIZE * 5.0f,
    .direction = {1.0f, 0.0f},
    .position = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
    .body =
        {
            {100.0f + DEFAULT_BOX_SIZE, 100.0f},
            {100.0f, 100.0f},
            {100.0f + 2 * DEFAULT_BOX_SIZE, 100.0f},
        },
    .grow = false,

};

static const Apple DefaultApple = {
    .position =
        {GetRandomValue(0, (SCREEN_WIDTH / DEFAULT_BOX_SIZE) - 1) * DEFAULT_BOX_SIZE +
             (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
         GetRandomValue(0, (SCREEN_HEIGHT / DEFAULT_BOX_SIZE) - 1) * DEFAULT_BOX_SIZE +
             (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f},
    .size = DEFAULT_BOX_SIZE / 2.0f,
};

static const GameState DefaultGameState = {

};

int main(int argc, char* argv[])
{
  GameState gameState = DefaultGameState;
  Snake snake = DefaultSnake;
  Apple apple = DefaultApple;

  // Snake local variables
  float accumulatedDistance = 0.0f;
  const float smoothness = 10.0f;
  const float turnSmoothness = 2.0f;
  Vector2 newDirection = snake.direction;
  bool directionChanged = false;
  std::deque<Vector2> logicalPosition = snake.body;
  std::deque<Vector2> renderedPosition = logicalPosition;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(DEFAULT_TARGET_FPS);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Move Player
    {
      if (snake.direction.y != 0) {
        if (IsKeyPressed(KEY_A)) {
          newDirection = {-1.0f, 0.0f};
        }
        if (IsKeyPressed(KEY_D)) {
          newDirection = {1.0f, 0.0f};
        }
      }
      if (snake.direction.x != 0) {
        if (IsKeyPressed(KEY_S)) {
          newDirection = {0.0f, 1.0f};
        }
        if (IsKeyPressed(KEY_W)) {
          newDirection = {0.0f, -1.0f};
        }
      }

      if (newDirection.x != snake.direction.x && newDirection.y != snake.direction.y) {
        directionChanged = true;
        snake.direction = newDirection;
      }
      accumulatedDistance += snake.speed * GetFrameTime();

      if (accumulatedDistance >= snake.size) {
        Vector2 newLogicalPosition = {
            logicalPosition.front().x + snake.direction.x * snake.size,
            logicalPosition.front().y + snake.direction.y * snake.size,
        };

        newLogicalPosition.x = std::roundf(newLogicalPosition.x / snake.size) * snake.size;
        newLogicalPosition.y = std::roundf(newLogicalPosition.y / snake.size) * snake.size;

        logicalPosition.push_front(newLogicalPosition);

        if (!snake.grow) {
          logicalPosition.pop_back();
        }
        else {
          renderedPosition.push_front(renderedPosition.front());
          snake.grow = false;
        }

        accumulatedDistance -= snake.size;
      }

      for (size_t i = 0; i < renderedPosition.size(); ++i) {
        float interpolationFactor = directionChanged ? turnSmoothness : smoothness;
        renderedPosition[i].x +=
            (logicalPosition[i].x - renderedPosition[i].x) / interpolationFactor;
        renderedPosition[i].y +=
            (logicalPosition[i].y - renderedPosition[i].y) / interpolationFactor;
      }

      if (directionChanged) {
        directionChanged = false;
      }
    };

    // Update Apple
    {
      DrawRectangleRec(
          {
              apple.position.x,
              apple.position.y,
              apple.size,
              apple.size,
          },
          RED
      );

      float appleOffset = DEFAULT_BOX_SIZE + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f;

      Vector2 snakeHeadCenter = {
          renderedPosition[0].x + DEFAULT_BOX_SIZE / 2,
          renderedPosition[0].y + DEFAULT_BOX_SIZE / 2,
      };
      Vector2 appleCenter = {
          apple.position.x + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
          apple.position.y + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
      };

      if (DEBUG_ENABLED) {
        DrawCircleLinesV(snakeHeadCenter, DEFAULT_BOX_SIZE / 2 - 2, RED);
        DrawCircleLinesV(appleCenter, DEFAULT_BOX_SIZE / 2 - 2, GREEN);
      }

      if (CheckCollisionCircles(snakeHeadCenter, snake.size / 2 - 2, appleCenter, apple.size - 2)) {
        apple.position = {
            GetRandomValue(0, (SCREEN_WIDTH / DEFAULT_BOX_SIZE) - 1) * DEFAULT_BOX_SIZE +
                (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
            GetRandomValue(0, (SCREEN_HEIGHT / DEFAULT_BOX_SIZE) - 1) * DEFAULT_BOX_SIZE +
                (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f
        };

        gameState.score += 10;
        snake.grow = true;
      }
    };

    // Draw
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
      for (const auto& segment : renderedPosition) {
        DrawRectangleRec({segment.x, segment.y, snake.size, snake.size}, GREEN);
      }
    };

    EndDrawing();
  }

  CloseWindow();

  return 0;
};
