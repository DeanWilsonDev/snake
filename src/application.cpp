#include "application.h"
#include "game-settings.h"
#include "game-session.h"
#include "log.h"
#include "raylib.h"
#include "iwindow.h"
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

namespace SnakeGame {

Application::Application(const ApplicationParams& config)
    : session(config.session)
    , window(config.window)
    , renderer(config.renderer)
    , settings(config.settings)
    , ui(config.ui)

{
  LOG_TRACE("Initializing Application");
};

Application::~Application()
{
  delete this->window;
  delete this->session;
  delete this->renderer;
  delete this->ui;
}

void Application::run()
{
  std::cout << "Application is actually running, logging failing" << std::endl;
  LOG_TRACE("Beginning Application");
  const char* title = settings.windowTitle ? settings.windowTitle : "Untitled Game";
  LOG_DEBUG("Title: {}", title);
  char* windowTitle = strdup(settings.windowTitle);
  assert(windowTitle);
  this->window->createWindow(settings.windowWidth, settings.windowHeight, windowTitle);
  this->window->setTargetFPS(settings.targetFPS);

  char scoreBuffer[100] = {0};

  LOG_DEBUG("Window Should Close {}", this->window->shouldClose());

  while (!this->window->shouldClose()) {
    this->renderer->beginDrawing();
    this->renderer->clearBackground(BLACK);

    switch (this->session->getState()) {
      case STATE_MAIN_MENU:
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
        this->renderer->draw();
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

    this->renderer->stopDrawing();
  }
  this->window->closeWindow();
}
}  // namespace SnakeGame
