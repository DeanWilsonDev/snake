#pragma once
#include "engine/dependency-injection/dependency-injector.hpp"
#include "config/engine-config.hpp"
#include "debug/i-debug-hud.hpp"
#include <memory>

namespace Core {
class IGame;
class IStateMachine;
class IGameState;
class RenderComponent2DManager;
class IRenderer;
}  // namespace Core

namespace UserInterface {
class IUserInterface;
}

namespace Platform {
namespace Input {
class IInputBackend;
}
namespace Window {
class IWindow;
}
}  // namespace Platform

namespace Engine {

namespace Config {
struct EngineConfig;
struct ProjectSettings;
}  // namespace Config

struct ApplicationParams {
  Engine::DependencyInjector& injector;
  Config::EngineConfig& engineConfig;
  Config::ProjectSettings& projectSettings;
  Core::RenderComponent2DManager& renderComponent2dManager;
};

class Application {
 public:
  explicit Application(const ApplicationParams& params);
  ~Application();

  void SetGame(std::shared_ptr<Core::IGame> game);
  void Run() const;

 private:
  Engine::DependencyInjector& injector;
  Config::EngineConfig& engineConfig;
  Config::ProjectSettings& projectSettings;
  std::shared_ptr<Core::IGame> game = nullptr;
  std::shared_ptr<Core::IStateMachine> stateMachine = nullptr;
  std::shared_ptr<Platform::Window::IWindow> window = nullptr;
  std::shared_ptr<Core::IRenderer> renderer2d = nullptr;
  std::shared_ptr<Platform::Input::IInputBackend> input = nullptr;
  std::shared_ptr<UserInterface::IUserInterface> userInterface = nullptr;
  std::shared_ptr<Debug::IDebugHUD> debugHud = nullptr;
  Core::RenderComponent2DManager& renderComponent2dManager;
};
}  // namespace Engine
