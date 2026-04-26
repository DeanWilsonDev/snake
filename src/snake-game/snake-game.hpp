#pragma once

#include "engine/game/game.hpp"

    namespace SnakeGame
{
  class SnakeGame : public Engine::Game {
   public:
    SnakeGame();
    void Initialize();
  };
}  // namespace SnakeGame
