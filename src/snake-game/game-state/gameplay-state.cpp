#include "gameplay-state.hpp"
#include "core/state/i-game-state.hpp"
#include "debug/debug.hpp"
#include "snake-game/game-state/game-over-state.hpp"
#include "gameplay-state-machine.hpp"
#include "physics/collision/components/collider-component-2d.hpp"
#include "snake-game/game-entities/snake-head.hpp"
#include "physics/collision/rectangle-collider-2d.hpp"
#include "snake-game/game-entities/snake.hpp"
#include "snake-game/game-entities/apple.hpp"
#include "core/logging/log.hpp"

#include <memory>
#include <cstddef>
#include <cassert>

namespace Renderer2D {
class IRenderer;
}

namespace SnakeGame {

GameplayState::GameplayState(GameContext& gameContext) : gameContext(gameContext) {}

void GameplayState::Enter()
{
  // if (!this->snake) {
  //   LOG_FATAL("[GameplayState] Snake is not initialized");
  //   assert(this->snake);
  // }
  //
  // if (!this->apple) {
  //   LOG_FATAL("[GameplayState] Snake is not initialized");
  //   assert(this->apple);
  // }

  // snake->SetActive(true);
  // apple->SetActive(true);

  // MAIN QUEST: Display UI Dynamically
  // this->gameplayStateMachine.SetGameUI(*this->gameplayUI);
}

void GameplayState::Update(float)
{
  // MAIN QUEST: Wire input to event bus
  // Input polling should be replaced with event-driven input. The input system
  // publishes InputActionEvents onto the event bus when actions are pressed.
  // Entities and systems subscribe to those events rather than polling directly.
  // See Engine::Events::IEventBus and Core::Input::Action for existing pieces.
  // if (this->gameContext.input->IsActionPressed(Core::Input::Action::MoveLeft)) {
  //   this->snake->SetDirection({-1.0f, 0.0f});
  // }
  // if (this->gameContext.input->IsActionPressed(Core::Input::Action::MoveRight)) {
  //   this->snake->SetDirection({1.0f, 0.0f});
  // }
  // if (this->gameContext.input->IsActionPressed(Core::Input::Action::MoveDown)) {
  //   this->snake->SetDirection({0.0f, 1.0f});
  // }
  // if (this->gameContext.input->IsActionPressed(Core::Input::Action::MoveUp)) {
  //   this->snake->SetDirection({0.0f, -1.0f});
  // }

  if (Physics::Collision::RectangleCollider2D::Intersects(
          this->snake->head->GetColliderComponent().GetCollider().GetWorldRect(),
          this->apple->GetColliderComponent().GetCollider().GetWorldRect()
      )) {
    LOG_DEBUG("[GameplayState] Snake got the Apple!");

    // this->apple->GetTransformComponent().SetPosition(this->apple->GetNewPosition());

    this->gameContext.score += 10;

    this->snake->SetGrow(true);
  }

  for (size_t i = 0; i < snake->body.size(); i++) {
    if (snake->body[i] == nullptr) {
      break;
    }

    if (snake->head != nullptr && snake->body[i] != snake->head) {
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

void GameplayState::DebugUpdate() const
{
  UMBRA_DEBUG(this->snake->body.size(), "Snake/Length");
}

void GameplayState::DebugRender() const {}

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

std::unique_ptr<Core::State::IGameState> GameplayState::GetNextState()
{
  return std::make_unique<GameOverState>(this->gameContext);
};

}  // namespace SnakeGame
