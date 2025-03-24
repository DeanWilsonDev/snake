#pragma once

class Snake;
class Apple;

enum State {
  STATE_MAIN_MENU,
  STATE_GAMEPLAY,
  STATE_GAME_OVER,
};

class GameState {
 public:
  GameState();
  ~GameState();

  void update();

  void addSnake(Snake* snake) { this->snake = snake; };
  Snake* getSnake() { return this->snake; };

  void addApple(Apple* apple) { this->apple = apple; };
  Apple* getApple() { return this->apple; };

  State getState() { return this->state; };
  void setState(State state) { this->state = state; };

  int getScore() { return this->score; };
  void increaseScore();

 private:
  Snake* snake;
  Apple* apple;
  State state;
  int score;
};
