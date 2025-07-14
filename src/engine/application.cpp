#include "application.h"
#include "log.h"
#include "config/project-settings.hpp"
#include "core/dependency-injector.hpp"
#include "core/color.h"
#include "renderer-2d/irenderer.h"

#include <cassert>
#include <cstring>
#include "game/game-state/gameplay-state-machine.hpp"
#include "platform/window/iwindow.h"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "core/igame.hpp"

namespace Engine {

// Main Quest: [Application] Update Application class. move items from main to application and tidy
// up

Application::Application(const ApplicationParams& params)
    : injector(params.injector)
    , engineConfig(params.engineConfig)
    , projectSettings(params.projectSettings)
    , renderComponent2dManager(params.renderComponent2dManager)
{
  LOG_TRACE("Initializing Application");
  this->window = injector.Resolve<Platform::Window::IWindow>();
  this->renderer2d = injector.Resolve<Renderer2D::IRenderer>();
  this->stateMachine = injector.Resolve<Core::IStateMachine>();
  this->input = injector.Resolve<Platform::Input::IInput>();
  this->userInterface = injector.Resolve<UserInterface::IUserInterface>();

  LOG_TRACE("Validating Dependencies");
  assert(this->window);
  assert(this->renderer2d);
  assert(this->stateMachine);
  assert(this->input);
  assert(this->userInterface);
};

Application::~Application() = default;

void Application::SetGame(std::shared_ptr<Core::IGame> game)
{
  this->game = std::move(game);
  if (this->game) {
    this->game->Initialize();
  }
}

void Application::Run() const
{
  LOG_TRACE("Beginning Application");
  const char* title = projectSettings.GetTitle() ?: engineConfig.window.title;
  LOG_INFO("Starting Game: {}", title);
  char* windowTitle = strdup(title);
  assert(windowTitle);

  this->window->CreateWindow(engineConfig.window.width, engineConfig.window.height, windowTitle);
  this->window->SetTargetFPS(engineConfig.window.targetFPS);

  LOG_DEBUG("Window Should Close {}", this->window->ShouldClose());

  std::chrono::time_point lastTime = std::chrono::high_resolution_clock::now();

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
    this->renderer2d->EndDrawing();
  }
  this->window->CloseWindow();
}
}  // namespace Engine
