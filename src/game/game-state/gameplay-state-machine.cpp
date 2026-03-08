
#include "gameplay-state-machine.hpp"
#include "core/state-machine.hpp"
#include "core/entity/game-entity-manager.hpp"
#include "game-over-state.hpp"
#include "gameplay-state.hpp"
#include "main-menu-state.hpp"
#include "core/i-game-ui.hpp"
#include "user-interface/i-user-interface.hpp"
#include "core/i-game-state.hpp"

#include <umbra/log.h>
#include <memory>
#include <assert.h>
#include <utility>

namespace Game {

GameplayStateMachine::GameplayStateMachine(std::unique_ptr<Core::IGameState> currentState)
    : StateMachine(std::move(currentState))
{
  if (!currentState) {
    Core::StateMachine::ChangeState(std::make_unique<MainMenuState>(this->gameContext));
  }
}

GameplayStateMachine::~GameplayStateMachine() {}

void GameplayStateMachine::Update(const float deltaTime)
{
  this->gameEntityManager->Update(deltaTime);

  Core::StateMachine::Update(deltaTime);

  // REAPER: Curious... This should go somewhere else
  // if (this->gameUI) {
  //   this->gameUI->Render();
  // }
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

}  // namespace Game
