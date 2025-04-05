#pragma once
#include "game-settings.h"
#include "game-state.h"
#include "irenderer.h"
#include "iuser-interface.h"
#include "iwindow.h"

namespace SnakeGame {

struct ApplicationParams {
  GameState* gameState;
  IWindow* window;
  IRenderer* renderer;
  IUserInterface* ui;
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
  IUserInterface* ui;
  GameSettings gameSettings;
};
}  // namespace SnakeGame
