#include "gameplay-state-machine.h"

#include "game-over-state.hpp"
#include "gameplay-state.hpp"
#include "../../renderer-2d/render-manager.hpp"
#include "log.h"
#include "main-menu-state.hpp"
#include "../../core/iuser-interface.hpp"

namespace Game {

GameplayStateMachine::GameplayStateMachine(Core::IGameState* currentState)
    : currentState(currentState), score(0)
{
}

GameplayStateMachine::~GameplayStateMachine()
{
  if (currentState) {
    currentState->Exit();
    delete this->currentState;
  }
}

void GameplayStateMachine::Update(float deltaTime)
{
  if (!this->currentState) return;
  this->currentState->Update(deltaTime);

  if (!this->renderManager) return;
  this->renderManager->RenderAll();

  if (!this->ui) return;
  this->ui->Render();
}

void GameplayStateMachine::ChangeState(Core::IGameState* newState)
{
  if (currentState) {
    currentState->Exit();
    delete this->currentState;
  }
  this->currentState = newState;
  if (currentState) {
    currentState->Enter();
  }
}

void GameplayStateMachine::IncreaseScore()
{
  this->score += 10;
}
void GameplayStateMachine::Next()
{
  if (!currentState) return;

  if (Core::IGameState* nextState = this->DetermineNextState()) {
    this->ChangeState(nextState);
  }
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
}
Core::IGameState* GameplayStateMachine::DetermineNextState()
{
  if (dynamic_cast<MainMenuState*>(this->currentState)) {
    return new GameplayState(this);
  }

  if (dynamic_cast<GameplayState*>(this->currentState)) {
    return new GameOverState(this);
  }

  if (dynamic_cast<GameOverState*>(this->currentState)) {
    return new GameplayState(this);
  }

  return nullptr;
};

}  // namespace Game
