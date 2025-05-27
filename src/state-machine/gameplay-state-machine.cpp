//
// Created by Dean Wilson on 27/5/2025.
//

#include "gameplay-state-machine.h"

GameplayStateMachine::GameplayStateMachine()
{

}

GameplayStateMachine::~GameplayStateMachine()
{

}

void update(float deltaTime) { currentState->update(deltaTime); }
void render() { currentState->render(); }


void GameplayStateMachine::changeState(IGameState* newState)
{
  delete currentState;
  currentState = newState;
}

GameSettings& GameplayStateMachine::getSettings()
{
  return this->settings;
}

GameSession& GameplayStateMachine::getGameSession()
{
  return this->session;
}

IUserInterface& GameplayStateMachine::getUI()
{
  return this->ui;
}