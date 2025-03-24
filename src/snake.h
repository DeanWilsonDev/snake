#pragma once

#include "constants.h"
#include "game-state.h"
#include "raylib.h"
#include "snake-body.h"
#include <deque>

class GameState;

struct Snake {
 public:
  Snake(GameState* state);

  void update();

  void move();
  void destroy();

  float size = DEFAULT_BOX_SIZE;
  float speed = DEFAULT_BOX_SIZE * 5.0f;
  int length = 3;
  Vector2 direction = {1.0f, 0.0f};
  SnakeBody* head;
  std::deque<SnakeBody*> body;
  bool grow = false;

 private:
  GameState* state;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
};
