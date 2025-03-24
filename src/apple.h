#pragma once

#include "game-state.h"
#include "raylib.h"
#include "constants.h"

class Apple {
 public:
  Apple(GameState* state, Snake* snake);

  void update();

  GameState* state;
  Snake* snake;
  Vector2 position;
  float size;
};
