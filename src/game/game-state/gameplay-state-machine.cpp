#include "gameplay-state-machine.hpp"

#include "game-over-state.hpp"
#include "gameplay-state.hpp"
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
  if (!this->currentState) {
    return;
  }

  this->currentState->Update(deltaTime);

  if (this->gameUI) {
    this->gameUI->Render();
  }
}

void GameplayStateMachine::ChangeState(Core::IGameState* newState)
{
  if (currentState) {
    currentState->Exit();
    delete currentState;
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
  this->snake = &snake;
};

void GameplayStateMachine::SetApple(Apple& apple)
{
  this->apple = &apple;
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
