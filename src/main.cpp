#include <MacTypes.h>
#include "application.h"
#include "game-settings.h"
#include "irenderer.h"
#include "iuser-interface.h"
#include "raylib-renderer.h"
#include "raylib-ui.h"
#include "raylib-ui.h"
#include "raylib-window.h"
#include "game-state.h"

class IWindow;

int main(int argc, char* argv[])
{
  GameSettings settings = {};
  GameState* gameState = new GameState(settings);
  IWindow* window = new RaylibWindow();
  RaylibRendererParams rendererParams = { .state = gameState, .settings= settings};
  IRenderer* renderer = new RaylibRenderer(rendererParams);
  IUserInterface* ui = new RaylibUI();

  const ApplicationParams applicationParams = {
      .gameState = gameState, .window = window, .gameSettings = settings, .renderer = renderer
  };
  Application* application = new Application(applicationParams);

  delete application;
  delete window;
  delete gameState;

  return 0;
};
