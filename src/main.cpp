#include <MacTypes.h>
#include "raylib.h"
#include <iostream>
#include <cmath>
#include <deque>
#include <cstdio>

#define SCREEN_WIDTH (500)
#define SCREEN_HEIGHT (500)
#define DEFAULT_TARGET_FPS (60)
#define DEFAULT_BOX_SIZE (20.0f)
#define DEBUG_ENABLED false

#define WINDOW_TITLE "Snake"

enum State {
  STATE_MAIN_MENU,
  STATE_GAMEPLAY,
  STATE_GAME_OVER,
};

struct Apple {
  Vector2 position;
  float size;
};

struct SnakeBody {
  int index;
  Vector2 position;
  Rectangle bounds;
  float size = DEFAULT_BOX_SIZE;

  SnakeBody(int index, Vector2 position) : index(index), position(position), bounds(getBounds())
  {
    DEBUG_ENABLED&& std::cout << "Creating SnakeBody with index: " << this->index
                              << " at position (" << this->position.x << ", " << this->position.y
                              << ")" << std::endl;
  }

  Rectangle getBounds()
  {
    this->bounds.x = this->position.x;
    this->bounds.y = this->position.y;
    this->bounds.width = this->size;
    this->bounds.height = this->size;
    return this->bounds;
  };
};

struct Snake {
  float size = DEFAULT_BOX_SIZE;
  float speed = DEFAULT_BOX_SIZE * 5.0f;
  int length = 3;
  Vector2 direction = {1.0f, 0.0f};
  SnakeBody* head;
  std::deque<SnakeBody*> body;
  bool grow = false;

  Snake()
  {
    this->head = new SnakeBody(0, {100.0f, 100.0f});
    this->body.push_back(this->head);

    for (int i = 1; i < this->length; i++) {
      this->body.push_back(new SnakeBody(i, {100.0f - i * this->size, 100.0f}));
    }
  }

  void destroy()
  {
    if (!body.empty() && body.front() == head) {
      body.pop_front();
    }

    for (auto segment : body) {
      if (segment) {
        DEBUG_ENABLED&& std::cout << "Deleting body segment at address: " << segment << std::endl;
        delete segment;
        DEBUG_ENABLED&& std::cout << "Body segment at address: " << segment
                                  << " successfully destroyed" << std::endl;
      }
      else {
        DEBUG_ENABLED&& std::cout << "Found null segment in body!" << std::endl;
      }
    }

    this->body.clear();

    if (head) {
      DEBUG_ENABLED&& std::cout << "Deleting head at address: " << this->head << std::endl;
      delete this->head;
      DEBUG_ENABLED&& std::cout << "Setting head to nullptr" << std::endl;
      this->head = nullptr;
      DEBUG_ENABLED&& std::cout << "Head successfully destroyed" << std::endl;
    }
    else {
      DEBUG_ENABLED&& std::cout << "Found null segment in head!" << std::endl;
    }
  }
};

struct GameState {
  State state;
  int score;
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
    .score = 0,
};

void draw_text_centered(const char* text, Vector2 position, float fontSize)
{
  const Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
  position.x -= textSize.x / 2.0f;
  DrawText(text, position.x, position.y, fontSize, WHITE);
}

int main(int argc, char* argv[])
{
  GameState gameState = DefaultGameState;
  Snake snake = Snake();
  Apple apple = DefaultApple;

  // Snake local variables
  float accumulatedDistance = 0.0f;
  const float smoothness = 10.0f;
  const float turnSmoothness = 2.0f;
  Vector2 newDirection = snake.direction;
  bool directionChanged = false;

  // Initialize the initial snake body
  // TODO: this can probably go in the snakes contructor

  std::deque<Vector2> renderedPosition;
  for (int i = 0; i < snake.body.size(); i++) {
    renderedPosition.push_back(snake.body[i]->position);
  }

  char scoreBuffer[100] = {0};

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(DEFAULT_TARGET_FPS);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (gameState.state) {
      case STATE_MAIN_MENU:
        draw_text_centered("Snake", (Vector2){SCREEN_WIDTH / 2.0f, 40}, 80);
        draw_text_centered("Press 'Enter' to start", (Vector2){SCREEN_WIDTH / 2.0f, 200.0f}, 20);
        if (IsKeyPressed(KEY_ENTER)) {
          gameState = DefaultGameState;
          gameState.state = STATE_GAMEPLAY;
        }
        break;
      case STATE_GAMEPLAY:
        std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", gameState.score);
        draw_text_centered(scoreBuffer, (Vector2){50, 30}, 20);

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
                snake.head->position.x + snake.direction.x * snake.size,
                snake.head->position.y + snake.direction.y * snake.size,
            };

            newLogicalPosition.x = std::roundf(newLogicalPosition.x / snake.size) * snake.size;
            newLogicalPosition.y = std::roundf(newLogicalPosition.y / snake.size) * snake.size;

            DEBUG_ENABLED&& std::cout << "Snake Body Size: " << snake.body.size() << std::endl;
            DEBUG_ENABLED&& std::cout << "Snake length: " << snake.length << std::endl;
            Vector2 previousPosition = snake.head->position;
            Vector2 nextPosition = snake.head->position;

            for (int i = 1; i < snake.length; i++) {
              DEBUG_ENABLED&& std::cout << "Body[" << i << "]: " << snake.body[i] << std::endl;
              DEBUG_ENABLED&& std::cout << "snake.body[" << i
                                        << "].x: " << snake.body[i]->position.x << std::endl;
              DEBUG_ENABLED&& std::cout << "snake.body[" << i
                                        << "].y: " << snake.body[i]->position.y << std::endl;

              if (snake.body[i] && snake.body[i - 1]) {
                previousPosition = snake.body[i]->position;
                snake.body[i]->position.x = nextPosition.x;
                snake.body[i]->position.y = nextPosition.y;
                nextPosition = previousPosition;
              }

              DEBUG_ENABLED&& std::cout << "snake.body[" << i - 1
                                        << "].x: " << snake.body[i - 1]->position.x << std::endl;
              DEBUG_ENABLED&& std::cout << "snake.body[" << i - 1
                                        << "].y: " << snake.body[i - 1]->position.y << std::endl;
            }

            snake.head->position.x = newLogicalPosition.x;
            snake.head->position.y = newLogicalPosition.y;
            if (snake.grow) {
              snake.body.push_back(new SnakeBody(snake.length, snake.body.back()->position));
              snake.length++;
              snake.grow = false;
            }

            accumulatedDistance -= snake.size;
          }

          if (snake.head) {
            DEBUG_ENABLED&& std::cout << "HEAD: " << snake.head << std::endl;
          }

          for (int i = 0; i < snake.body.size(); i++) {
            DEBUG_ENABLED&& std::cout << "Body[" << i << "]: " << snake.body[i] << std::endl;
            if (snake.head != nullptr && snake.body[i] != snake.head) {
              if (DEBUG_ENABLED) {
                DrawRectangleRec(snake.body[i]->getBounds(), RED);
              }

              if (CheckCollisionRecs(snake.head->getBounds(), snake.body[i]->getBounds())) {
                gameState.state = STATE_GAME_OVER;
              }
            }
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
              snake.head->position.x + DEFAULT_BOX_SIZE / 2,
              snake.head->position.y + DEFAULT_BOX_SIZE / 2,
          };
          Vector2 appleCenter = {
              apple.position.x + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
              apple.position.y + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
          };

          if (DEBUG_ENABLED) {
            DrawCircleLinesV(snakeHeadCenter, DEFAULT_BOX_SIZE / 2 - 2, RED);
            DrawCircleLinesV(appleCenter, DEFAULT_BOX_SIZE / 2 - 2, GREEN);
          }

          if (CheckCollisionCircles(
                  snakeHeadCenter, snake.size / 2 - 2, appleCenter, apple.size - 2
              )) {
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
          for (const auto& segment : snake.body) {
            DrawRectangleRec(
                {segment->position.x, segment->position.y, snake.size, snake.size}, GREEN
            );
          }
        };
        break;
      case STATE_GAME_OVER:
        draw_text_centered("Game Over", (Vector2){SCREEN_WIDTH / 2.0f, 40}, 80);
        draw_text_centered("Press 'Enter' to start", (Vector2){SCREEN_WIDTH / 2.0f, 200.0f}, 20);
        std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", gameState.score);
        draw_text_centered(scoreBuffer, (Vector2){SCREEN_WIDTH / 2.0f, 100}, 20);
        if (IsKeyPressed(KEY_ENTER)) {
          snake.destroy();
          snake = Snake();
          gameState = DefaultGameState;
          gameState.state = STATE_GAMEPLAY;
        }
        break;
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
};
