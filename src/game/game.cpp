//
// Created by Dean Wilson on 14/7/2025.
//

#include "game.hpp"

#include <umbra/log.h>
#include "core/dependency-injector.hpp"
#include "core/i-game-state.h"
#include "debug/debug.hpp"
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

  if (this->snake) {
    delete this->snake;
    this->snake = nullptr;
  }

  if (this->apple) {
    delete this->apple;
    this->apple = nullptr;
  }

  if (this->settings) {
    delete this->settings;
    this->settings = nullptr;
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

  this->settings = new GameSettings{};
  settings->Print();

  // Initialize Snake
  LOG_TRACE("[Game] Setting up Snake GameObject");

  const auto snakeParams = SnakeParams{.input = *input, .settings = *settings};

  this->snake = new Snake(snakeParams);
  this->snake->Initialize();
  LOG_DEBUG("[Game] Snake set to [{}]", static_cast<void*>(&snake));

  // Initialize Apple
  LOG_TRACE("[Game] Setting up Apple GameObject");

  this->apple = new Apple({
      .settings = *settings,
  });

  LOG_DEBUG(
      "[Apple] Checking GameSettings is Initialized: [{}]", static_cast<void*>(&this->settings)
  );

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

  LOG_DEBUG(
      "[Game] Checking GameSettings on Snake [{}]",
      static_cast<void*>(&this->gameplayStateMachine->GetSnake()->GetGameSettings())
  );

  this->gameplayStateMachine->SetRenderManager(this->renderManager);
  this->gameplayStateMachine->SetRenderer(*renderer);
  this->gameplayStateMachine->SetUserInterface(*userInterface);
  this->gameplayStateMachine->SetInput(*input);
  this->gameplayStateMachine->SetGameSettings(*settings);

  this->renderManager.Register(snake->head->GetRendererComponent2D());
  for (const auto segment : this->snake->body) {
    if (const auto segmentRenderComponent = segment->GetRendererComponent2D()) {
      this->renderManager.Register(segmentRenderComponent);
    }
  }
  this->renderManager.Register(apple->GetRendererComponent2D());

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
