#pragma once

#include "game-settings.h"
#include "game-state.h"
#include "snake-body.h"
#include <deque>
#include "raylib.h"

class GameState;

struct SnakeParams {
  GameState* state;
  GameSettings& settings;
};

class Snake {
 public:
  Snake(const SnakeParams& snakeParams);

  void update();
  void destroy();

  float size;
  float speed;
  int length;
  Vector2 direction;
  SnakeBody* head;
  std::deque<SnakeBody*> body;
  bool grow = false;

 private:
  GameState* state;
  GameSettings settings;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
};
