#include "game-state.h"
#include "game-settings.h"
#include "snake.h"
#include "apple.h"

GameState::GameState(GameSettings settings) : settings(settings)
{
  settings.Print();
  this->state = STATE_MAIN_MENU;
  this->score = 0;
  SnakeParams snakeParams = {.state = this, .settings = settings};
  Snake* snake = new Snake(snakeParams);
  addSnake(snake);
  AppleParams appleParams = {
      .settings = settings,
      .snake = snake,
      .state = this,
  };
  addApple(new Apple(appleParams));
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
  apple->update();
}
