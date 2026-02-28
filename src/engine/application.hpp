#pragma once
#include "config/engine-config.h"
#include "core/entity/game-entity-manager.hpp"
#include "debug/i-debug-hud.hpp"
#include <memory>

namespace Renderer2D {
class RenderComponent2DManager;
}
namespace Core {
class DependencyInjector;
class IGame;
class IStateMachine;
class IGameState;
}  // namespace Core

namespace Renderer2D {
class IRenderer;
}

namespace UserInterface {
class IUserInterface;
}

namespace Platform {
namespace Input {
class IInput;
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
  Core::DependencyInjector& injector;
  Config::EngineConfig& engineConfig;
  Config::ProjectSettings& projectSettings;
  Renderer2D::RenderComponent2DManager& renderComponent2dManager;
};

class Application {
 public:
  explicit Application(const ApplicationParams& params);
  ~Application();

  void SetGame(std::shared_ptr<Core::IGame> game);
  void Run() const;

 private:
  Core::DependencyInjector& injector;
  Config::EngineConfig& engineConfig;
  Config::ProjectSettings& projectSettings;
  std::shared_ptr<Core::IGame> game = nullptr;
  std::shared_ptr<Core::IStateMachine> stateMachine = nullptr;
  std::shared_ptr<Platform::Window::IWindow> window = nullptr;
  std::shared_ptr<Renderer2D::IRenderer> renderer2d = nullptr;
  std::shared_ptr<Platform::Input::IInput> input = nullptr;
  std::shared_ptr<UserInterface::IUserInterface> userInterface = nullptr;
  std::shared_ptr<Debug::IDebugHUD> debugHud = nullptr;
  Renderer2D::RenderComponent2DManager& renderComponent2dManager;
  Core::GameEntityManager& gameEntityManager;
};
}  // namespace Engine
