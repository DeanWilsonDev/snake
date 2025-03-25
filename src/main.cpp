#include <MacTypes.h>
#include "application.h"
#include "game-settings.h"
#include "raylib-window.h"
#include "raylib.h"
#include <cstdio>
#include "snake.h"
#include "apple.h"
#include "game-state.h"
#include "user-interface.h"

class IWindow;

int main(int argc, char* argv[])
{
  GameState* gameState = new GameState();
  IWindow* window = new RaylibWindow();
  GameSettings settings = {};
  Application* application = new Application(gameState, window, settings);

  delete application;
  delete window;
  delete gameState;

  return 0;
};
