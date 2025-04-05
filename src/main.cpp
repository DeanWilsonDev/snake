#include "application.h"
#include "game-settings.h"
#include "irenderer.h"
#include "iuser-interface.h"
#include "raylib-renderer.h"
#include "raylib-ui.h"
#include "raylib-ui.h"
#include "raylib-window.h"
#include "game-state.h"
#include "log.h"
#include "core.h"

class IWindow;

int main(int argc, char* argv[])
{
  // Initialize Logging
  Umbra::Logging::Log::init(DEBUG_ENABLED);
  LOG_DEBUG("Debug Log Working {}", 1);
  LOG_WARNING("Warning Log Working {}", 2);
  LOG_CORE_ERROR("Core Logging Working {}", 3);

  GameSettings settings = {.windowTitle = "Snake"};
  GameState* gameState = new GameState(settings);
  IWindow* window = new RaylibWindow();
  RaylibRendererParams rendererParams = {
      .settings = settings,
      .state = gameState,
  };
  IRenderer* renderer = new RaylibRenderer(rendererParams);
  IUserInterface* ui = new RaylibUI();

  const SnakeGame::ApplicationParams applicationParams = {
      .gameState = gameState,
      .window = window,
      .renderer = renderer,
      .ui = ui,
      .gameSettings = settings,
  };

  SnakeGame::Application* application = new SnakeGame::Application(applicationParams);

  application->run();
  return 0;
};
