#include "gameplay-state-machine.h"

#include "log.h"
#include "game-states/igame-state.h"
#include "../game/game-settings.h"
#include "../renderer-2d/render-manager.h"

GameplayStateMachine::GameplayStateMachine(
    IGameState* currentState, GameSettings& settings
)
    : currentState(currentState), settings(settings), score(0)
{

}

GameplayStateMachine::~GameplayStateMachine() = default;

void GameplayStateMachine::Update(float deltaTime)
{
  this->currentState->Update(deltaTime);
  this->renderManager->RenderAll();
}

void GameplayStateMachine::ChangeState(IGameState* newState)
{
  delete currentState;
  currentState = newState;
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

void AddApple(Apple* apple)
{
  LOG_TRACE("Adding Apple to Game State");
  this->apple = apple;
  LOG_TRACE("Apple Added to Game State");
};
