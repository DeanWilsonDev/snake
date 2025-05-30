#include "engine/application.h"
#include "core/iuser-interface.h"
#include "raylib/renderer/raylib-renderer.h"
#include "raylib/user-interface/raylib-ui.h"
#include "raylib/window/raylib-window.h"
#include "game-session.h"
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
  GameSession* session = new GameSession(settings);
  IWindow* window = new RaylibWindow();
  RaylibRendererParams rendererParams = {
      .settings = settings,
      .session = session,
  };
  IRenderer* renderer = new RaylibRenderer(rendererParams);
  IUserInterface* ui = new RaylibUI();
  Game* game = new Game();

  const Core::ApplicationParams applicationParams = {
      .session = session,
      .window = window,
      .renderer = renderer,
      .ui = ui,
      .settings = settings,
      .game = game,
  };

  Engine::Application* application = new Engine::Application(applicationParams);

  application->Run();
  return 0;
};
