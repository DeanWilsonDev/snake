#pragma once

class GameState;
class Snake;

class Draw {
 public:
  Draw(GameState* state) { this->state = state; };

  void draw();

 private:
  GameState* state;
};
