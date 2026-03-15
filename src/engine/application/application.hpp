#pragma once
#include "core/i-application.hpp"
#include "debug/debug-hud.hpp"
#include "engine/game/game.hpp"
#include "engine/config/application-config.hpp"
#include "core/i-dependency-injector.hpp"
#include "engine/config/engine-config.hpp"
#include "core/debug/i-debug-hud.hpp"
#include <memory>

namespace Core {
class IGame;
namespace State {
class IStateMachine;
class IGameState;
}  // namespace State
namespace Rendering {
class RenderComponent2DManager;
class IRenderer;
}  // namespace Rendering
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

class Application : public Core::IApplication {
 public:
  explicit Application(std::unique_ptr<Game> game);
  ~Application();

  virtual void Run() override;
  void SetGame(std::unique_ptr<Core::IGame> game);

 protected:
  virtual void Initialize() override;
  virtual void Configure(Config::ApplicationConfig& config) override;
  virtual void RegisterDependencies(Core::IDependencyInjector& injector) override;
  virtual void Update(float deltaTime) override;
  virtual void DebugUpdate() override;
  virtual void Render() override;
  virtual void DebugRender() override;
  virtual void Shutdown() override;
  [[nodiscard]] virtual Config::ApplicationConfig& GetConfig() override { return *this->config; };

 private:
  std::unique_ptr<Core::IGame> game = nullptr;
  std::unique_ptr<Core::IDependencyInjector> injector;
  std::unique_ptr<Platform::Window::IWindow> window = nullptr;
  std::unique_ptr<Platform::Input::IInputBackend> input = nullptr;
  std::unique_ptr<Core::Rendering::IRenderer> renderer = nullptr;
  std::unique_ptr<Core::Rendering::RenderComponent2DManager> renderComponent2dManager;
  Config::ApplicationConfig config;

  std::unique_ptr<Debug::DebugHUD> debugHUD;

  // std::shared_ptr<UserInterface::IUserInterface> userInterface = nullptr;
  std::shared_ptr<Core::Debug::IDebugHUD> debugHud = nullptr;
  std::shared_ptr<Core::State::IStateMachine> stateMachine = nullptr;
};
}  // namespace Engine
