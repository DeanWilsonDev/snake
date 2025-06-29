#include "game-session.h"
#include "game/settings/game-settings.h"
#include "log.h"
#include "game/snake.hpp"
#include "game/apple.hpp"

GameSession::GameSession(GameSettings settings) : settings(settings)
{
  // Main Quest: [GameSession] Delete Game Session file. Remove this file once everything has been migrated
  settings.Print();
  this->state = STATE_MAIN_MENU;
  this->score = 0;
  SnakeParams snakeParams = {.session = this, .settings = settings};
  Snake* snake = new Snake(snakeParams);
  addSnake(snake);
  AppleParams appleParams = {
      .settings = settings,
      .session = this,
      .snake = snake,
  };
  addApple(new Apple(appleParams));
  LOG_TRACE("Finish Initializing GameSession");
}

GameSession::~GameSession()
{
  // On destroy of the state machine probably
  this->snake->destroy();
  // delete this->snake;
  delete this->apple;
}

// This is the Update function of the gameplay loop.
void GameSession::update()
{
  LOG_TRACE("Being GameSession Update");
  snake->update();
  apple->update();
}
