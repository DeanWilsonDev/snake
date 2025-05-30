#include "gameplay-state-machine.h"
#include "../../renderer-2d/render-manager.h"
#include "log.h"
#include "../../core/iuser-interface.h"

namespace Game {

GameplayStateMachine::GameplayStateMachine(Core::IGameState* currentState)
    : currentState(currentState), score(0)
{
}

void GameplayStateMachine::Update(float deltaTime)
{
  if (!this->currentState) return;
  if (!this->renderManager) return;
  this->currentState->Update(deltaTime);
  this->renderManager->RenderAll();

  if (!this->ui) return;
  this->ui->Render();
}

void GameplayStateMachine::ChangeState(Core::IGameState* newState)
{
  delete this->currentState;
  this->currentState = newState;
}

void GameplayStateMachine::IncreaseScore()
{
  this->score += 10;
}

void GameplayStateMachine::SetSnake(Snake& snake)
{
  LOG_TRACE("Adding Snake to Game State");
  this->snake = &snake;
  LOG_TRACE("Snake Added to Game State");
};

void GameplayStateMachine::SetApple(Apple& apple)
{
  LOG_TRACE("Adding Apple to Game State");
  this->apple = &apple;
  LOG_TRACE("Apple Added to Game State");
};
}  // namespace Game
