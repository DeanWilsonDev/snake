#include "gameplay-state-machine.h"

#include "log.h"
#include "game-states/igame-state.h"
#include "../game-settings.h"

GameplayStateMachine::GameplayStateMachine(
    IGameState* currentState, GameSettings settings, IUserInterface* ui, Snake* snake, Apple* apple
)
    : currentState(currentState), settings(settings), ui(ui), snake(snake), apple(apple), score(0)
{
  this->renderComponents = new std::vector<Component::IRenderable*>();
}

GameplayStateMachine::~GameplayStateMachine() = default;

void Update(float deltaTime)
{
  this->currentState->update(deltaTime);
}

void GameplayStateMachine::ChangeState(IGameState* newState)
{
  delete currentState;
  currentState = newState;
}
IGameState* GameplayStateMachine::GetState()
{
  return currentState;
}

GameSettings& GameplayStateMachine::GetSettings()
{
  return this->settings;
}

GameSession& GameplayStateMachine::GetGameSession()
{
  return this->session;
}

IUserInterface& GameplayStateMachine::GetUI()
{
  return this->ui;
}
void GameplayStateMachine::IncreaseScore()
{
  this->score += 10;
}

void AddSnake(Snake* snake)
{
  LOG_TRACE("Adding Snake to Game State");
  this->snake = snake;
  LOG_TRACE("Snake Added to Game State");
};
Snake* GetSnake()
{
  return this->snake;
};

void AddApple(Apple* apple)
{
  LOG_TRACE("Adding Apple to Game State");
  this->apple = apple;
  LOG_TRACE("Apple Added to Game State");
};
Apple* GetApple()
{
  return this->apple;
};
