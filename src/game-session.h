#pragma once

#include "game/game-settings.h"
#include "log.h"
class Snake;
class Apple;

enum State {
  STATE_MAIN_MENU,
  STATE_GAMEPLAY,
  STATE_GAME_OVER,
};

class GameSession {
 public:
  GameSession(GameSettings settings);
  ~GameSession();

  void update();

  void setState(State state) { this->state = state; };

  State getState() { return this->state; };
  int getScore() { return this->score; };
  void increaseScore();

  void changeState();
  void mainMenu();
  void gameplay();
  void gameOver();

 private:
  Snake* snake;
  Apple* apple;
  State state;
  GameSettings settings;
  int score;
};
