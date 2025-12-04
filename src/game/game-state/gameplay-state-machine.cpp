#include "gameplay-state-machine.hpp"

#include "game-over-state.hpp"
#include "gameplay-state.hpp"
#include <umbra/log.h>
#include "main-menu-state.hpp"
#include "game/game-objects/apple.hpp"
#include "game/game-objects/snake.hpp"
#include "user-interface/i-game-ui.hpp"
#include "user-interface/i-user-interface.hpp"

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

void GameplayStateMachine::Update(const float deltaTime)
{
  LOG_DEBUG("[GameplayStateMachine] Running Update Function");
  if (!this->currentState) {
    return;
  }

  LOG_DEBUG("[GameplayStateMachine] Running Current State Update Function");
  this->currentState->Update(deltaTime);

  LOG_DEBUG("[GameplayStateMachine] checking GameUI [{}]", static_cast<void*>(&this->gameUI));
  if (this->gameUI) {
    LOG_DEBUG("[GameplayStateMachine] Rendering GameUI");
    this->gameUI->Render();
  }
}

void GameplayStateMachine::ChangeState(Core::IGameState* newState)
{
  LOG_DEBUG("[GameplayStateMachine] Changing State");
  if (currentState) {
    currentState->Exit();
    delete currentState;
  }
  LOG_DEBUG("[GameplayStateMachine] Setting state to [{}]", static_cast<void*>(&newState));
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
  LOG_TRACE("[GameplayStateMachine] Running Next state");
  if (!currentState) return;
  if (Core::IGameState* nextState = this->DetermineNextState()) {
    LOG_DEBUG("[GameplayStateMachine] Next State: [{}]", static_cast<void*>(&nextState));
    this->ChangeState(nextState);
  }
}
void GameplayStateMachine::InitializeSnake() const
{
  if (this->snake) {
    this->snake->Initialize();
  }
}

void GameplayStateMachine::InitializeApple() const
{
  if (this->apple) {
    this->apple->Initialize();
  }
}

void GameplayStateMachine::SetSnake(Snake& snake)
{
  LOG_TRACE("[GameplayStateMachine] Adding Snake to Game State");
  this->snake = &snake;
  LOG_TRACE(
      "[GameplayStateMachine] Snake [{}] Added to Game State", static_cast<void*>(&this->snake)
  );
};

void GameplayStateMachine::SetApple(Apple& apple)
{
  LOG_TRACE("[GameplayStateMachine] Adding Apple to Game State");
  this->apple = &apple;
  LOG_TRACE(
      "[GameplayStateMachine] Apple [{}] Added to Game State", static_cast<void*>(&this->apple)
  );
}
void GameplayStateMachine::SetUserInterface(UserInterface::IUserInterface& ui)
{
  if (this->userInterface != nullptr) {
    this->userInterface = nullptr;
  }
  this->userInterface = &ui;
}

void GameplayStateMachine::SetGameUI(UserInterface::IGameUI& gameUI)
{
  if (this->gameUI != nullptr) {
    this->gameUI = nullptr;
  }
  this->gameUI = &gameUI;
}

Core::IGameState* GameplayStateMachine::DetermineNextState()
{
  if (dynamic_cast<MainMenuState*>(this->currentState)) {
    return new GameplayState(*this);
  }

  if (dynamic_cast<GameplayState*>(this->currentState)) {
    return new GameOverState(*this);
  }

  if (dynamic_cast<GameOverState*>(this->currentState)) {
    return new GameplayState(*this);
  }

  return nullptr;
};

}  // namespace Game
