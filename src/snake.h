#pragma once

#include "game-settings.h"
#include "game-session.h"
#include "snake-body.h"
#include <deque>
#include "raylib.h"

class GameState;

struct SnakeParams {
  GameSession* session;
  GameSettings& settings;
};

class Snake {
 public:
  Snake(const SnakeParams& snakeParams);

  void update();
  void destroy();
  void move();
  void checkIfShouldGrow();
  void teleport();

  float size;
  float speed;
  int length;
  Vector2 direction;
  SnakeBody* head;
  std::deque<SnakeBody*> body;
  bool grow = false;

 private:
  GameSession* session;
  GameSettings settings;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
};
