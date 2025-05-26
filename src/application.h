#pragma once
#include "game-settings.h"
#include "irenderer.h"
#include "game-session.h"
#include "iuser-interface.h"
#include "game.h"
#include "iwindow.h"

namespace SnakeGame {

struct ApplicationParams {
  GameSession* session;
  IWindow* window;
  IRenderer* renderer;
  IUserInterface* ui;
  GameSettings settings;
  Game* game;
};

class Application {
 public:
  Application(const ApplicationParams& appData);
  ~Application();

  void run();

 private:
  GameSession* session;
  IWindow* window;
  IRenderer* renderer;
  IUserInterface* ui;
  GameSettings settings;
  Game* game;
};
}  // namespace SnakeGame
