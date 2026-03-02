#include "gameplay-state.hpp"
#include "debug/debug.hpp"
#include "engine/input/input-action.hpp"
#include "game/game-state/game-over-state.hpp"
#include "gameplay-state-machine.hpp"
#include "game/game-objects/snake.hpp"
#include "game/game-objects/apple.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "physics/collision/rectangle-collider-2d.hpp"
#include "game/game-objects/snake-segment.hpp"
#include "game/ui/gameplay-ui.hpp"
#include "umbra/log.h"

#include <memory>
#include <cstddef>
#include <cassert>

namespace Renderer2D {
class IRenderer;
}

namespace Game {

GameplayState::GameplayState(GameContext& gameContext) : gameContext(gameContext)
{
  // Initialize Snake
  LOG_TRACE("[GameplayState] Setting up Snake GameObject");
  const auto snakeParams = SnakeParams{.settings = *gameContext.settings};
  this->snake = make_unique<Snake>(snakeParams);
  LOG_DEBUG("[GameplayState] Snake set to [{}]", static_cast<void*>(&snake));
  this->snake->Initialize();

  //
  // Initialize Apple
  //

  AppleParams appleParams = AppleParams(*gameContext.settings);
  LOG_TRACE("[Game] Setting up Apple GameObject");
  this->apple = make_unique<Apple>(appleParams);
  LOG_DEBUG("[Game] Apple set to [{}]", static_cast<void*>(&this->apple));

  // const auto userInterface = this->gameplayStateMachine.GetUserInterface();

  // assert(gameSettings);
  // assert(userInterface);
  // this->gameplayUI = new GameplayUI(*userInterface, *gameSettings, score);
}

void GameplayState::Enter()
{
  if (!this->snake) {
    LOG_FATAL("[GameplayState] Snake is not initialized");
    assert(this->snake);
  }

  if (!this->apple) {
    LOG_FATAL("[GameplayState] Snake is not initialized");
    assert(this->apple);
  }

  LOG_DEBUG("[GameplayState] Initializing Apple");
  apple->Initialize();

  snake->SetActive(true);
  apple->SetActive(true);

  // MAIN QUEST: Display UI Dynamically
  // this->gameplayStateMachine.SetGameUI(*this->gameplayUI);
}

void GameplayState::Update(float)
{
  if (this->gameContext.input->IsActionPressed(Engine::Input::Action::MoveLeft)) {
    this->snake->SetDirection({-1.0f, 0.0f});
  }
  if (this->gameContext.input->IsActionPressed(Engine::Input::Action::MoveRight)) {
    this->snake->SetDirection({1.0f, 0.0f});
  }
  if (this->gameContext.input->IsActionPressed(Engine::Input::Action::MoveDown)) {
    this->snake->SetDirection({0.0f, 1.0f});
  }
  if (this->gameContext.input->IsActionPressed(Engine::Input::Action::MoveUp)) {
    this->snake->SetDirection({0.0f, -1.0f});
  }

  if (Physics::Collision::RectangleCollider2D::Intersects(
          this->snake->head->GetColliderComponent().GetCollider().GetWorldRect(),
          this->apple->GetColliderComponent().GetCollider().GetWorldRect()
      )) {
    LOG_DEBUG("[GameplayState] Snake got the Apple!");
    this->apple->GetTransformComponent().SetPosition(this->apple->GetNewPosition());

    this->gameContext.score += 10;

    this->snake->SetGrow(true);
  }

  for (size_t i = 0; i < snake->body.size(); i++) {
    if (snake->body[i] == nullptr) {
      break;
    }

    if (snake->head != nullptr && snake->body[i].get() != snake->head) {
      // Side Quest: [Debug] Create a Debug module to allow for Debug drawing
      // if (this->debugEnabled) {
      //   DrawRectangleRec(snake->body[i]->GetBounds(), RED);
      // }

      // if (snake->head->GetColliderComponent()->Intersects(*snake->body[i]->GetColliderComponent()
      //     )) {
      //   LOG_INFO("[GameplayState] Head hit body part with index: {}", i);
      //   this->gameplayStateMachine.Next();
      // }
    }
  }
}

void GameplayState::DebugUpdate()
{
  UMBRA_DEBUG(this->snake->body.size(), "Snake/Length");
}

void GameplayState::Exit()
{
  // MAIN QUEST: FIX UI
  // if (gameplayUI != nullptr) {
  //   delete gameplayUI;
  //   gameplayUI = nullptr;
  // }
  //
  // this->gameplayStateMachine.ClearUI();
}

std::unique_ptr<Core::IGameState> GameplayState::GetNextState()
{
  return std::make_unique<GameOverState>(this->gameContext);
};

}  // namespace Game
