#pragma once
#include "game-settings.h"
#include "game-state.h"
#include "irenderer.h"
#include "istate-context.h"
#include "iuser-interface.h"
#include "game.h"
#include "iwindow.h"

namespace SnakeGame {

struct ApplicationParams {
  GameSession* session;
  IWindow* window;
  IRenderer* renderer;
  IUserInterface* ui;
  GameSettings* gameSettings;
  Game* game;
};

class Application {
 public:
  Application(const ApplicationParams& appData);
  ~Application();

  void run();

 private:
  IStateContext GameSession* session;
  IWindow* window;
  IRenderer* renderer;
  IUserInterface* ui;
  GameSettings* gameSettings;
  Game* game;
};
}  // namespace SnakeGame
