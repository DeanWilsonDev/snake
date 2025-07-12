#pragma once
#include "config/engine-config.h"
#include "core/implementation-manager.hpp"
#include "platform/input/input.hpp"

namespace Core {
class DependencyInjector;
}
namespace Core {
class IStateMachine;
class IGameState;
}  // namespace Core

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

namespace Config {
struct EngineConfig;
struct ProjectSettings;
}  // namespace Config

struct ApplicationParams {
  Core::DependencyInjector& injector;
  Config::EngineConfig& engineConfig;
  Config::ProjectSettings& projectSettings;
};

class Application {
 public:
  explicit Application(const ApplicationParams& params);
  ~Application();

  void Run();

 private:
  // Main Quest: [Application] Remove Implementation Managers
  // Core::ImplementationManager<Platform::Window::IWindow>& window;
  // Core::ImplementationManager<Renderer2D::IRenderer>& renderer;
  // Core::ImplementationManager<UserInterface::IUserInterface>& ui;

  Core::DependencyInjector& injector;
  Config::EngineConfig& engineConfig;
  Config::ProjectSettings& projectSettings;
  std::shared_ptr<Core::IStateMachine> stateMachine = nullptr;
  std::shared_ptr<Platform::Window::IWindow> window = nullptr;
  std::shared_ptr<Renderer2D::IRenderer> renderer2d = nullptr;
  std::shared_ptr<Platform::Input::IInput> input = nullptr;
  std::shared_ptr<UserInterface::IUserInterface> userInterface = nullptr;
};
}  // namespace Engine
