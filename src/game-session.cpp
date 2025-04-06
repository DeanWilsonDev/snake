#include "game-session.h"
#include "game-settings.h"
#include "log.h"
#include "snake.h"
#include "apple.h"

GameSession::GameSession(GameSettings settings) : settings(settings)
{
  settings.Print();
  this->state = STATE_MAIN_MENU;
  this->score = 0;
  SnakeParams snakeParams = {.state = this, .settings = settings};
  Snake* snake = new Snake(snakeParams);
  addSnake(snake);
  AppleParams appleParams = {
      .settings = settings,
      .state = this,
      .snake = snake,
  };
  addApple(new Apple(appleParams));
  LOG_TRACE("Finish Initializing GameSession");
}

GameSession::~GameSession()
{
  this->snake->destroy();
  // delete this->snake;
  delete this->apple;
}

void GameSession::increaseScore()
{
  this->score += 10;
}

void GameSession::update()
{
  LOG_TRACE("Being GameSession Update");
  snake->update();
  apple->update();
}
