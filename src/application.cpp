#include "application.h"
#include "game-settings.h"
#include "game-state.h"
#include "log.h"
#include "raylib.h"
#include "iwindow.h"
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

namespace SnakeGame {

Application::Application(const ApplicationParams& config)
    : gameState(config.gameState)
    , window(config.window)
    , renderer(config.renderer)
    , gameSettings(config.gameSettings)
    , ui(config.ui)

{
  LOG_TRACE("Initializing Application");
};

Application::~Application()
{
  delete this->window;
  delete this->gameState;
  delete this->renderer;
  delete this->ui;
}

void Application::run()
{
  std::cout << "Application is actually running, logging failing" << std::endl;
  LOG_TRACE("Beginning Application");
  const char* title = gameSettings.windowTitle ? gameSettings.windowTitle : "Untitled Game";
  LOG_DEBUG("Title: {}", title);
  char* windowTitle = strdup(gameSettings.windowTitle);
  assert(windowTitle);
  this->window->createWindow(gameSettings.windowWidth, gameSettings.windowHeight, windowTitle);
  this->window->setTargetFPS(gameSettings.targetFPS);

  char scoreBuffer[100] = {0};

  LOG_DEBUG("Window Should Close {}", this->window->shouldClose());

  while (!this->window->shouldClose()) {
    this->renderer->beginDrawing();
    this->renderer->clearBackground(BLACK);

    switch (this->gameState->getState()) {
      case STATE_MAIN_MENU:
        ui->drawTextCentered("Snake", (Vector2){gameSettings.windowWidth / 2.0f, 40.0f}, 80);
        ui->drawTextCentered(
            "Press 'Enter' to start", (Vector2){gameSettings.windowWidth / 2.0f, 200.0f}, 20
        );
        if (IsKeyPressed(KEY_ENTER)) {
          this->gameState->setState(STATE_GAMEPLAY);
        }
        break;
      case STATE_GAMEPLAY:
        LOG_TRACE("Begin Gameplay Loop");
        std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", this->gameState->getScore());
        ui->drawTextCentered(scoreBuffer, (Vector2){80, 30}, 20);
        this->gameState->update();
        this->renderer->draw();
        break;
      case STATE_GAME_OVER:
        ui->drawTextCentered("Game Over", (Vector2){gameSettings.windowWidth / 2.0f - 40, 40}, 80);
        ui->drawTextCentered(
            "Press 'Enter' to start", (Vector2){gameSettings.windowWidth / 2.0f, 200.0f}, 20
        );
        std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", this->gameState->getScore());
        ui->drawTextCentered(scoreBuffer, (Vector2){gameSettings.windowWidth / 2.0f, 150.0f}, 20);
        if (IsKeyPressed(KEY_ENTER)) {
          delete this->gameState;
          this->gameState = new GameState(this->gameSettings);
          this->gameState->setState(STATE_GAMEPLAY);
        }
        break;
    }

    this->renderer->stopDrawing();
  }
  this->window->closeWindow();
}
}  // namespace SnakeGame
