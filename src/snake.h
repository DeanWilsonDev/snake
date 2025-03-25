#pragma once

#include "game-settings.h"
#include "game-state.h"
#include "raylib.h"
#include "snake-body.h"
#include <deque>

class GameState;

class Snake {
 public:
  Snake(GameState* state, GameSettings settings);

  void update();

  void move();
  void destroy();

 private:
  float size;
  float speed;
  int length;
  Vector2 direction;
  SnakeBody* head;
  std::deque<SnakeBody*> body;
  bool grow = false;
  GameState* state;
  GameSettings settings;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
};
