#include "raylib.h"
#include <cmath>
#include <deque>
#include <random>
#include <iostream>

#define SCREEN_WIDTH (500)
#define SCREEN_HEIGHT (500)
#define DEFAULT_TARGET_FPS (60)
#define DEFAULT_BOX_SIZE (20.0f)
#define DEBUG_ENABLED true

#define WINDOW_TITLE "Snake"

float get_random_value(int maxRange)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, maxRange);

  return dist(gen);
}

struct GameState {
  // Player
  float playerSize;
  float playerSpeed;
  int playerLength;
  Vector2 playerDirection;
  Vector2 playerPosition;
  std::deque<Vector2> playerBody;
  bool playerGrow;

  // Apple
  Vector2 applePosition;

  int score;
};

static const GameState DefaultGameState = {
    .playerSize = DEFAULT_BOX_SIZE,
    .playerSpeed = DEFAULT_BOX_SIZE * 5.0f,
    .playerLength = 3,
    .playerDirection = {1.0f, 0.0f},
    .playerPosition = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
    .playerBody =
        {
            {100.0f + DEFAULT_BOX_SIZE, 100.0f},
            {100.0f, 100.0f},
            {100.0f + 2 * DEFAULT_BOX_SIZE, 100.0f},
        },
    .playerGrow = false,

    .applePosition = {get_random_value(SCREEN_WIDTH), get_random_value(SCREEN_HEIGHT)}
};

int main(int argc, char* argv[])
{
  GameState gameState = DefaultGameState;
  float accumulatedDistance = 0.0f;
  const float smoothness = 10.0f;

  std::deque<Vector2> logicalPosition = gameState.playerBody;
  std::deque<Vector2> renderedPosition = logicalPosition;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(DEFAULT_TARGET_FPS);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Move Player
    {
      if (gameState.playerDirection.y != 0) {
        if (IsKeyPressed(KEY_A)) {
          gameState.playerDirection = {-1.0f, 0.0f};
        }
        if (IsKeyPressed(KEY_D)) {
          gameState.playerDirection = {1.0f, 0.0f};
        }
      }
      if (gameState.playerDirection.x != 0) {
        if (IsKeyPressed(KEY_S)) {
          gameState.playerDirection = {0.0f, 1.0f};
        }
        if (IsKeyPressed(KEY_W)) {
          gameState.playerDirection = {0.0f, -1.0f};
        }
      }

      accumulatedDistance += gameState.playerSpeed * GetFrameTime();

      if (accumulatedDistance >= gameState.playerSize) {
        Vector2 newLogicalPosition = {
            logicalPosition.front().x + gameState.playerDirection.x * gameState.playerSize,
            logicalPosition.front().y + gameState.playerDirection.y * gameState.playerSize,
        };

        newLogicalPosition.x =
            std::roundf(newLogicalPosition.x / gameState.playerSize) * gameState.playerSize;
        newLogicalPosition.y =
            std::roundf(newLogicalPosition.y / gameState.playerSize) * gameState.playerSize;

        logicalPosition.push_front(newLogicalPosition);

        if (!gameState.playerGrow) {
          logicalPosition.pop_back();
        }
        else {
          gameState.playerGrow = false;
        }

        accumulatedDistance -= gameState.playerSize;
      }

      for (size_t i = 0; i < renderedPosition.size(); ++i) {
        renderedPosition[i].x += (logicalPosition[i].x - renderedPosition[i].x) / smoothness;
        renderedPosition[i].y += (logicalPosition[i].y - renderedPosition[i].y) / smoothness;
      }
    };

    // Update Apple
    {

    };

    // Draw
    {
      // DEBUG: Draw Grid
      if (DEBUG_ENABLED) {
        for (int x = 0; x < SCREEN_WIDTH; x += gameState.playerSize) {
          DrawLine(x, 0, x, SCREEN_HEIGHT, {255, 255, 255, 40});
        }

        for (int y = 0; y < SCREEN_HEIGHT; y += gameState.playerSize) {
          DrawLine(0, y, SCREEN_WIDTH, y, {255, 255, 255, 40});
        }
      }

      // Draw Snake
      for (const auto& segment : renderedPosition) {
        DrawRectangleRec({segment.x, segment.y, gameState.playerSize, gameState.playerSize}, GREEN);
      }

      DrawCircle(gameState.applePosition.x, gameState.applePosition.y, DEFAULT_BOX_SIZE / 2, RED);
      std::cout << "Apple X: " << gameState.applePosition.x << std::endl;
      std::cout << "Apple Y: " << gameState.applePosition.y << std::endl;
    };

    EndDrawing();
  }

  CloseWindow();

  return 0;
};
