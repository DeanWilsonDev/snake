//
// Created by Dean Wilson on 14/7/2025.
//

#include "game.hpp"

#include <umbra/log.h>
#include "core/dependency-injector.hpp"
#include "core/i-game-state.h"
#include "game-objects/apple.hpp"
#include "game-objects/snake.hpp"
#include "game-state/gameplay-state-machine.hpp"
#include "platform/window/i-window.h"
#include "platform/input/i-input.hpp"
#include "renderer-2d/i-renderer.h"
#include "user-interface/i-user-interface.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "renderer-2d/components/render-component-2d.h"
#include "settings/game-settings.h"
#include "core/i-state-machine.hpp"
#include "game-state/main-menu-state.hpp"
#include "game-objects/snake-segment.hpp"

#include <cassert>
#include <memory>

namespace Game {

Game::Game(
    Core::DependencyInjector& injector, Engine::Config::ProjectSettings& projectSettings,
    Renderer2D::RenderComponent2DManager& renderManager
)
    : injector(injector), projectSettings(projectSettings), renderManager(renderManager)
{
}
Game::~Game()
{
  if (this->gameplayStateMachine) {
    delete this->gameplayStateMachine;
    this->gameplayStateMachine = nullptr;
  }
}

void Game::Initialize()
{
  // Initialize Settings

  LOG_TRACE("[Game] Initializing Game");
  LOG_TRACE("[Game] Resolving Window");
  const shared_ptr<Platform::Window::IWindow> window =
      injector.Resolve<Platform::Window::IWindow>();

  const auto input = injector.Resolve<Platform::Input::IInput>();
  if (!input) {
    LOG_FATAL("[Game] Failed to initialize Input");
    assert(input);
  }

  LOG_TRACE("[Game] Validating Window");
  assert(window);

  this->settings = make_unique<GameSettings>();

  LOG_DEBUG("[Game] GameSettings is set to [{}]", static_cast<void*>(&this->settings));

  settings->Print();

  // Initialize Snake
  LOG_TRACE("[Game] Setting up Snake GameObject");

  const auto snakeParams = SnakeParams{.input = *input, .settings = *settings};

  this->snake = make_unique<Snake>(snakeParams);

  LOG_DEBUG("[Game] Snake set to [{}]", static_cast<void*>(&snake));

  this->snake->Initialize();

  //
  // Initialize Apple
  //

  AppleParams appleParams = AppleParams(*settings);

  LOG_TRACE("[Game] Setting up Apple GameObject");

  this->apple = make_unique<Apple>(appleParams);

  LOG_DEBUG("[Game] Apple set to [{}]", static_cast<void*>(&this->apple));

  const auto renderer = injector.Resolve<Renderer2D::IRenderer>();
  if (!renderer) {
    LOG_FATAL("[Game] Failed to initialize Renderer");
    assert(renderer);
  }

  const auto userInterface = injector.Resolve<UserInterface::IUserInterface>();
  if (!renderer) {
    LOG_FATAL("[Game] Failed to initialize UserInterface");
    assert(userInterface);
  }

  LOG_DEBUG("[Game] Resolving GameplayStateMachine");
  const auto stateMachine = injector.Resolve<Core::IStateMachine>();
  this->gameplayStateMachine = dynamic_cast<GameplayStateMachine*>(stateMachine.get());

  LOG_DEBUG(
      "[Game] GameplayStateMachine set to: [{}]", static_cast<void*>(&this->gameplayStateMachine)
  );

  if (!this->gameplayStateMachine) {
    LOG_FATAL("[Game] Failed to initialize GameplayStateMachine");
    assert(this->gameplayStateMachine);
  }

  Core::IGameState* initialState = new MainMenuState(*this->gameplayStateMachine);
  this->gameplayStateMachine->SetApple(*this->apple);
  this->gameplayStateMachine->SetSnake(*this->snake);

  LOG_TRACE("[Game] Setup Gameplay State Machine");

  this->gameplayStateMachine->SetRenderManager(this->renderManager);

  LOG_TRACE("[Game] Set Renderer on Gameplay State Machine");
  assert(renderer);
  this->gameplayStateMachine->SetRenderer(*renderer);
  LOG_TRACE("[Game] Set UserInterface on Gameplay State Machine");
  assert(userInterface);
  this->gameplayStateMachine->SetUserInterface(*userInterface);
  LOG_TRACE("[Game] Set Input on Gameplay State Machine");
  assert(input);
  this->gameplayStateMachine->SetInput(*input);
  LOG_TRACE("[Game] Set Settings on Gameplay State Machine");
  assert(settings);
  this->gameplayStateMachine->SetGameSettings(*settings);

  for (const auto& segment : this->snake->body) {
    assert(segment);
    this->renderManager.Register(&segment->GetRendererComponent2D());
  }
  this->renderManager.Register(&apple->GetRendererComponent2D());

  this->gameplayStateMachine->GetGameSettings()->Print();

  this->gameplayStateMachine->ChangeState(initialState);
}

void Game::Update(const float deltaTime)
{
  if (this->gameplayStateMachine != nullptr) {
    this->gameplayStateMachine->Update(deltaTime);
  }
}

void Game::DebugUpdate()
{
  if (this->snake) {
    for (const auto& segment : this->snake->body) {
      segment->DebugUpdate();
    }
  }

  if (this->apple) {
    this->apple->DebugUpdate();
  }
}

void Game::Render()
{
  this->renderManager.RenderAll();
}

}  // namespace Game
