#include "application.h"
#include "log.h"
#include "raylib.h"
#include "config/project-settings.hpp"
#include "core/dependency-injector.hpp"

#include <iostream>
#include <cassert>
#include <cstring>
#include "game/game-state/gameplay-state-machine.hpp"
#include "platform/window/iwindow.h"

namespace Engine {

// Main Quest: [Application] Update Application class. move items from main to application and tidy
// up

Application::Application(const ApplicationParams& params)
    : injector(params.injector)
    , engineConfig(params.engineConfig)
    , projectSettings(params.projectSettings)
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

void Application::Run()
{
  LOG_TRACE("Beginning Application");
  const char* title = projectSettings.GetTitle() ? engineConfig.window.title : "Untitled Game";
  LOG_INFO("Starting Game: {}", title);
  char* windowTitle = strdup(title);
  assert(windowTitle);

  this->window->CreateWindow(engineConfig.window.width, engineConfig.window.height, windowTitle);
  this->window->SetTargetFPS(
      engineConfig.window.targetFPS
  );

  LOG_DEBUG("Window Should Close {}", this->window->ShouldClose());

  while (!this->window->ShouldClose()) {
    this->renderer2d->BeginDrawing();
    this->renderer2d->ClearBackground(BLACK);

    switch (this->session->getState()) {
      case Game::STATE_MAIN_MENU:
        ui->drawTextCentered("Snake", (Vector2){settings.windowWidth / 2.0f, 40.0f}, 80);
        ui->drawTextCentered(
            "Press 'Enter' to start", (Vector2){settings.windowWidth / 2.0f, 200.0f}, 20
        );
        if (IsKeyPressed(KEY_ENTER)) {
          this->session->setState(STATE_GAMEPLAY);
        }
        break;
      case STATE_GAMEPLAY:
        LOG_TRACE("Begin Gameplay Loop");
        std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", this->session->getScore());
        ui->drawTextCentered(scoreBuffer, (Vector2){80, 30}, 20);
        this->session->update();
        this->renderer->Draw();
        break;
      case STATE_GAME_OVER:
        ui->drawTextCentered("Game Over", (Vector2){settings.windowWidth / 2.0f - 40, 40}, 80);
        ui->drawTextCentered(
            "Press 'Enter' to start", (Vector2){settings.windowWidth / 2.0f, 200.0f}, 20
        );
        std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", this->session->getScore());
        ui->drawTextCentered(scoreBuffer, (Vector2){settings.windowWidth / 2.0f, 150.0f}, 20);
        if (IsKeyPressed(KEY_ENTER)) {
          delete this->session;
          this->session = new GameSession(this->settings);
          this->session->setState(STATE_GAMEPLAY);
        }
        break;
    }

    this->renderer->StopDrawing();
  }
  this->window->closeWindow();
}
}  // namespace Engine
