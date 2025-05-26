#pragma once

#include "game-settings.h"
#include "game-session.h"
#include "raylib.h"

struct AppleParams {
  GameSettings settings;
  GameSession* session;
  Snake* snake;
};

class Apple {
 public:
  Apple(const AppleParams& params);
  void update();
  Vector2 getNewPosition();

  GameSession* state;
  GameSettings settings;
  Snake* snake;
  Vector2 position;
  float size;
};
