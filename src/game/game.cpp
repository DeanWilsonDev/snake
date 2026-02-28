//
// Created by Dean Wilson on 14/7/2025.
//

#include "game.hpp"

#include <core/i-debugable.hpp>
#include <core/i-updatable.hpp>
#include <umbra/log.h>
#include "core/dependency-injector.hpp"
#include "core/entity/game-entity-manager.hpp"
#include "core/i-game-state.hpp"
#include "game-objects/apple.hpp"
#include "game-objects/snake.hpp"
#include "game-state/gameplay-state-machine.hpp"
#include "platform/window/i-window.h"
#include "platform/input/i-input.hpp"
#include "renderer-2d/i-renderer.hpp"
#include "user-interface/i-user-interface.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "renderer-2d/components/render-component-2d.hpp"
#include "settings/game-settings.hpp"
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
Game::~Game() {}

void Game::Initialize()
{
  // REAPER: Clean this file up
  // Ideally, it can act as internal plumbing and can live in the Core module.

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

  LOG_TRACE("[Game] Setting up GameEntityManager");
  this->gameEntityManager = std::make_shared<Core::GameEntityManager>(this->renderManager);

  this->settings = make_unique<GameSettings>();

  LOG_DEBUG("[Game] GameSettings is set to [{}]", static_cast<void*>(&this->settings));

  settings->Print();

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
  const shared_ptr<Core::IStateMachine> stateMachine = injector.Resolve<Core::IStateMachine>();
  this->gameplayStateMachine = dynamic_pointer_cast<GameplayStateMachine>(stateMachine);

  LOG_DEBUG(
      "[Game] GameplayStateMachine set to: [{}]", static_cast<void*>(&this->gameplayStateMachine)
  );

  if (!this->gameplayStateMachine) {
    LOG_FATAL(
        "[Game] Failed to initialize GameplayStateMachine, DI returned unexpected IStateMachine "
        "type!"
    );
    assert(this->gameplayStateMachine);
  }

  LOG_TRACE("[Game] Setup Gameplay State Machine");
  this->gameplayStateMachine->SetRenderManager(this->renderManager);

  LOG_TRACE("[Game] Set Renderer on Gameplay State Machine");
  assert(renderer);
  this->gameplayStateMachine->SetRenderer(*renderer);

  LOG_TRACE("[Game] Set GameEntityMangager on Gameplay State Machine");
  assert(this->gameEntityManager);
  this->gameplayStateMachine->SetGameEntityManager(this->gameEntityManager);

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

}

void Game::Update(const float deltaTime)
{
  if (this->gameplayStateMachine) {
    this->gameplayStateMachine->Update(deltaTime);
  }
}

void Game::DebugUpdate()
{
  if (this->gameplayStateMachine) {
    this->gameplayStateMachine->DebugUpdate();
  }
}

// MAIN QUEST: Think about renderables and who should be responsible for rendering them?
// GameEntityManager?
void Game::Render()
{
  this->renderManager.RenderAll();
}

}  // namespace Game
