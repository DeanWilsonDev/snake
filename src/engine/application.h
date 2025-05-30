#pragma once
#include "config/engine-config.h"

class IStateMachine;
struct GameSettings;
class IRenderer;
class IUserInterface;
class IWindow;
class IGameState;

namespace Engine {

struct ApplicationParams {
  IWindow& window;
  IRenderer* renderer = nullptr;
  IUserInterface* ui = nullptr;
  Config::EngineConfig engineConfig;

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
  Config::EngineConfig engineConfig;
  IStateMachine* stateMachine;
};
}  // namespace Engine
