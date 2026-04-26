
#include "gameplay-state-machine.hpp"
#include "engine/state/state-machine.hpp"
#include "core/entity/game-entity-manager.hpp"
#include "gameplay-state.hpp"
#include "main-menu-state.hpp"
#include "core/state/i-game-state.hpp"

#include <memory>
#include <assert.h>
#include <utility>

namespace SnakeGame {

GameplayStateMachine::GameplayStateMachine(std::unique_ptr<Core::State::IGameState> currentState)
    : StateMachine(std::move(currentState))
{
  if (!currentState) {
    Core::State::StateMachine::ChangeState(std::make_unique<MainMenuState>(this->gameContext));
  }
}

GameplayStateMachine::~GameplayStateMachine() {}

void GameplayStateMachine::Update(const float deltaTime)
{
  this->gameEntityManager->Update(deltaTime);

  Core::State::StateMachine::Update(deltaTime);
}

void GameplayStateMachine::DebugUpdate()
{
  if (this->gameEntityManager) {
    this->gameEntityManager->DebugUpdate();
  }
}

void GameplayStateMachine::SetGameEntityManager(
    std::shared_ptr<Core::GameEntityManager> gameEntityManager
)
{
  this->gameEntityManager = gameEntityManager;
}

}  // namespace SnakeGame
