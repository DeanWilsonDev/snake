#include "game-state.h"
#include "snake.h"
#include "apple.h"

GameState::GameState()
{
  this->state = STATE_MAIN_MENU;
  this->score = 0;
  Snake* snake = new Snake(this);
  addSnake(snake);
  addApple(new Apple(this, snake));
}

GameState::~GameState()
{
  this->snake->destroy();
  delete this->snake;
  delete this->apple;
}

void GameState::increaseScore()
{
  this->score += 10;
}

void GameState::update()
{
  snake->update();
}
