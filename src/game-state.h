#pragma once

#include "game-settings.h"
#include "log.h"
class Snake;
class Apple;

enum State {
  STATE_MAIN_MENU,
  STATE_GAMEPLAY,
  STATE_GAME_OVER,
};

class GameState {
 public:
  GameState(GameSettings settings);
  ~GameState();

  void update();

  void addSnake(Snake* snake)
  {
    LOG_TRACE("Adding Snake to Game State");
    this->snake = snake;
    LOG_TRACE("Snake Added to Game State");
  };
  Snake* getSnake() { return this->snake; };

  void addApple(Apple* apple)
  {
    LOG_TRACE("Adding Apple to Game State");
    this->apple = apple;
    LOG_TRACE("Apple Added to Game State");
  };
  Apple* getApple() { return this->apple; };

  State getState() { return this->state; };
  void setState(State state) { this->state = state; };

  int getScore() { return this->score; };
  void increaseScore();

 private:
  Snake* snake;
  Apple* apple;
  State state;
  GameSettings settings;
  int score;
};
