#include "application.h"
#include <umbra/log.h>
#include "config/project-settings.hpp"
#include "core/dependency-injector.hpp"
#include "core/color.h"
#include "renderer-2d/i-renderer.h"
#include "platform/input/i-input.hpp"
#include "user-interface/i-user-interface.hpp"
#include "debug/i-debug-hud.hpp"

#include <chrono>

#include <memory>
#include <cassert>
#include <cstring>
#include "game/game-state/gameplay-state-machine.hpp"
#include "platform/window/i-window.h"
#include "core/i-game.hpp"

namespace Engine {

Application::Application(const ApplicationParams& params)
    : injector(params.injector)
    , engineConfig(params.engineConfig)
    , projectSettings(params.projectSettings)
    , renderComponent2dManager(params.renderComponent2dManager)
{
  LOG_CORE_TRACE("[Application] Initializing");
  this->window = injector.Resolve<Platform::Window::IWindow>();
  this->renderer2d = injector.Resolve<Renderer2D::IRenderer>();
  this->stateMachine = injector.Resolve<Core::IStateMachine>();
  this->input = injector.Resolve<Platform::Input::IInput>();
  this->userInterface = injector.Resolve<UserInterface::IUserInterface>();
  this->debugHud = injector.Resolve<Debug::IDebugHUD>();

  LOG_CORE_TRACE("[Application] Window set to {}", static_cast<void*>(&window));
  LOG_CORE_TRACE("[Application] Renderer2D set to {}", static_cast<void*>(&renderer2d));
  LOG_CORE_TRACE("[Application] StateMachine set to {}", static_cast<void*>(&stateMachine));
  LOG_CORE_TRACE("[Application] Input set to {}", static_cast<void*>(&input));
  LOG_CORE_TRACE("[Application] UserInterface set to {}", static_cast<void*>(&userInterface));
  LOG_CORE_TRACE("[Application] DebugHUD set to {}", static_cast<void*>(&debugHud));

  LOG_CORE_TRACE("[Application] Validating Dependencies");
  assert(this->window);
  assert(this->renderer2d);
  assert(this->stateMachine);
  assert(this->input);
  assert(this->userInterface);
};

Application::~Application() = default;

void Application::SetGame(std::shared_ptr<Core::IGame> game)
{
  LOG_CORE_TRACE("[Application] Setting Game to {}", static_cast<void*>(&game));
  this->game = game;
  if (this->game) {
    this->game->Initialize();
  }
}

void Application::Run() const
{
  LOG_CORE_TRACE("[Application] Beginning Application");
  const char* title = projectSettings.GetTitle() ?: engineConfig.window.title;
  LOG_CORE_INFO("[Application] Starting Game: {}", title);
  char* windowTitle = strdup(title);
  LOG_CORE_DEBUG("[Application] Window Title set: {}", windowTitle);
  assert(windowTitle);

  if (!this->window) {
    LOG_CORE_FATAL("[Application] Failed to initialize window");
    assert(this->window);
  }
  this->window->CreateWindow(engineConfig.window.width, engineConfig.window.height, windowTitle);
  this->window->SetTargetFPS(engineConfig.window.targetFPS);

  LOG_CORE_DEBUG("[Application] Window Should Close {}", this->window->ShouldClose());

  std::chrono::time_point lastTime = std::chrono::high_resolution_clock::now();

  LOG_CORE_TRACE("[Application] Beginning application loop");
  while (!this->window->ShouldClose()) {
    // Calculate DeltaTime
    std::chrono::time_point currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - lastTime;
    const float deltaTime = elapsedTime.count();
    lastTime = currentTime;

    if (game) {
      this->game->Update(deltaTime);
    }

    this->renderer2d->BeginDrawing();
    this->renderer2d->ClearBackground(Core::COLOR_BLACK);
    if (game) {
      this->game->Render();
    }

    // MAIN QUEST: add debug mode check
    if (this->debugHud) {
      // MAIN QUEST: Enable Debug HUD
      // this->userInterface->RenderDebugHUD(this->debugHud)
    }

    this->renderer2d->EndDrawing();
  }
  this->window->CloseWindow();
}
}  // namespace Engine
