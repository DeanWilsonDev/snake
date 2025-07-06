#pragma once
#include "config/engine-config.h"

namespace Core {
class IStateMachine;
class IGameState;
}

namespace Renderer2D {
class IRenderer;
}

namespace UserInterface {
class IUserInterface;
}

namespace Platform::Window {
class IWindow;
}


namespace Engine {

struct ApplicationParams {
  Platform::Window::IWindow& window;
  Renderer2D::IRenderer* renderer = nullptr;
  UserInterface::IUserInterface* ui = nullptr;
  Config::EngineConfig engineConfig;

  Core::IStateMachine* stateMachine = nullptr;
};

class Application {
 public:
  explicit Application(const ApplicationParams& config);
  ~Application();

  void Run();

 private:
  Platform::Window::IWindow& window;
  Renderer2D::IRenderer* renderer;
  UserInterface::IUserInterface* ui;
  Config::EngineConfig engineConfig;
  Core::IStateMachine* stateMachine;
};
}  // namespace Engine
