
#include "gameplay-state-machine.hpp"
#include "engine/state/state-machine.hpp"
#include "engine/entities/entity-manager.hpp"
#include "gameplay-state.hpp"
#include "snake-game/game-state/main-menu-state.hpp"
#include "core/state/i-game-state.hpp"

#include <memory>
#include <assert.h>
#include <utility>

namespace SnakeGame {

GameplayStateMachine::GameplayStateMachine(std::unique_ptr<Core::State::IGameState> currentState)
    : StateMachine(std::move(currentState))
{
  if (!currentState) {
    Engine::State::StateMachine::ChangeState(std::make_unique<MainMenuState>(this->gameContext));
  }
}

GameplayStateMachine::~GameplayStateMachine() {}

void GameplayStateMachine::Update(const float deltaTime)
{
  Engine::State::StateMachine::Update(deltaTime);
}

void GameplayStateMachine::DebugUpdate() const
{
}

void GameplayStateMachine::DebugRender() const
{
}

}  // namespace SnakeGame
