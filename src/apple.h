#pragma once

#include "game-settings.h"
#include "game-state.h"
#include "types.h"

struct AppleParams {
  GameSettings settings;
  GameState* state;
  Snake* snake;
};

class Apple {
 public:
  Apple(const AppleParams& params);

  void update();
  Vector2 getNewPosition();

  GameState* state;
  GameSettings settings;
  Snake* snake;
  Vector2 position;
  float size;
};
