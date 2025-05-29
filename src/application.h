#pragma once
#include "game-settings.h"
#include "render-2d/irenderer.h"

class IStateMachine;
struct GameSettings;
class IRenderer;
class IUserInterface;
class IWindow;
class IGameState;

namespace Core {

struct ApplicationParams {
  IWindow& window;
  IRenderer* renderer = nullptr;
  IUserInterface* ui = nullptr;
  GameSettings settings;
  IStateMachine* stateMachine = nullptr;
};

class Application {
 public:
  explicit Application(const ApplicationParams& config);
  ~Application();

  void Run();

 private:
  IWindow& window;
  IRenderer* renderer;
  IUserInterface* ui;
  GameSettings settings;
  IStateMachine* stateMachine;
};
}  // namespace SnakeGame
