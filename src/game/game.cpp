//
// Created by Dean Wilson on 14/7/2025.
//

#include "game.hpp"

#include <core/i-debugable.hpp>
#include <core/i-updatable.hpp>
#include <umbra/log.h>
#include "engine/dependency-injection/dependency-injector.hpp"
#include "core/entity/game-entity-manager.hpp"
#include "game-objects/apple.hpp"
#include "game-objects/snake.hpp"
#include "game-state/gameplay-state-machine.hpp"
#include "platform/input/i-input-backend.hpp"
#include "platform/window/i-window.h"
#include "core/rendering/i-renderer.hpp"
#include "user-interface/i-user-interface.hpp"
#include "core/rendering/render-component-2d-manager.hpp"
#include "renderer-2d/components/render-component-2d.hpp"
#include "settings/game-settings.hpp"
#include "core/i-state-machine.hpp"
#include "game-objects/snake-segment.hpp"
#include "core/user-interface-manager.hpp"

#include <cassert>
#include <memory>

namespace Game {

Game::Game(
    Engine::DependencyInjector& injector, Engine::Config::ProjectSettings& projectSettings,
    Core::Rendering::RenderComponent2DManager& renderManager
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

  const auto input = injector.Resolve<Platform::Input::IInputBackend>();
  if (!input) {
    LOG_FATAL("[Game] Failed to initialize Input");
    assert(input);
  }

  LOG_TRACE("[Game] Validating Window");
  assert(window);

  LOG_TRACE("[Game] Setting up GameEntityManager");
  this->gameEntityManager = std::make_shared<Core::GameEntityManager>(this->renderManager);
  assert(this->gameEntityManager);

  LOG_TRACE("[Game] Setting up UserInterfaceManager");
  this->userInterfaceManager = std::make_shared<Core::UserInterfaceManager>(this->renderManager);

  this->settings = make_unique<GameSettings>();

  LOG_DEBUG("[Game] GameSettings is set to [{}]", static_cast<void*>(&this->settings));

  settings->Print();

  const auto renderer = injector.Resolve<Core::Rendering::IRenderer>();
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
  this->gameplayStateMachine->SetGameEntityManager(this->gameEntityManager);

  
  // for (const auto& segment : this->snake->body) {
  //   assert(segment);
  //   this->renderManager.Register(&segment->GetRendererComponent2D());
  // }
  // this->renderManager.Register(&apple->GetRendererComponent2D());
}

// MAIN QUEST: Think about renderables and updatables and who should be responsible for rendering
// them? GameEntityManager?

void Game::Update(const float deltaTime)
{
  if (this->gameplayStateMachine) {
    this->gameplayStateMachine->Update(deltaTime);
  }

  this->userInterfaceManager->Update(deltaTime);
}

void Game::DebugUpdate()
{
  if (this->gameplayStateMachine) {
    this->gameplayStateMachine->DebugUpdate();
  }

  this->userInterfaceManager->DebugUpdate();
}

void Game::DebugRender()
{
  this->userInterfaceManager->DebugRender();
}

void Game::Render()
{
  this->gameEntityManager->Render();

  this->userInterfaceManager->DebugRender();
}

}  // namespace Game
