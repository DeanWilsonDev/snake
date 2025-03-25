#pragma once
#include "game-settings.h"
#include "game-state.h"
#include "irenderer.h"
#include "iwindow.h"

struct ApplicationParams {
  GameState* gameState;
  IWindow* window;
  IRenderer* renderer;
  GameSettings gameSettings;
};

class Application {
 public:
  Application(const ApplicationParams& appData);
  ~Application();

  void run();

 private:
  GameState* gameState;
  IWindow* window;
  IRenderer* renderer;
  GameSettings gameSettings;
};
