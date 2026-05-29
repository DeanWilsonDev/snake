#pragma once
#include "core/events/i-event-bus.hpp"
#include "core/i-application.hpp"
#include "core/scenes/i-scene-manager.hpp"
#include "core/scenes/i-scene-manager.hpp"
#include "debug/debug-hud.hpp"
#include "engine/config/application-config.hpp"
#include "core/i-dependency-injector.hpp"
#include "core/debug/i-debug-hud.hpp"

// Main Quest: Move these to core
#include "platform/window/i-window.hpp"
#include "platform/input/i-input-backend.hpp"

#include <memory>

namespace Core {
namespace Scenes {
class ISceneManager;
}
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
  explicit Application();
  ~Application();

  virtual void Run() override;

 protected:
  virtual void Initialize() override;
  virtual void Configure(Config::ApplicationConfig& config) override;
  virtual void RegisterDependencies() override;
  virtual void Update(float deltaTime) override;
  virtual void DebugUpdate() override;
  virtual void Render() override;
  virtual void DebugRender() override;
  virtual void Shutdown() override;
  [[nodiscard]] virtual Config::ApplicationConfig& GetConfig() override { return this->config; };
  [[nodiscard]] virtual Core::IDependencyInjector& GetInjector() const override
  {
    return *this->injector;
  };

 private:
  std::unique_ptr<Core::IDependencyInjector> injector;
  std::shared_ptr<Platform::Window::IWindow> window = nullptr;
  std::shared_ptr<Platform::Input::IInputBackend> input = nullptr;
  std::shared_ptr<Core::Rendering::IRenderer> renderer = nullptr;
  std::shared_ptr<Core::Events::IEventBus> eventBus = nullptr;
  std::shared_ptr<Core::Rendering::RenderComponent2DManager> renderComponent2dManager;
  Config::ApplicationConfig config;

  std::unique_ptr<Debug::DebugHUD> debugHUD;

  std::shared_ptr<UserInterface::IUserInterface> userInterface = nullptr;
  std::shared_ptr<Core::Debug::IDebugHUD> debugHud = nullptr;
  std::shared_ptr<Core::State::IStateMachine> stateMachine = nullptr;
  std::shared_ptr<Core::Scenes::ISceneManager> sceneManager = nullptr;
};
}  // namespace Engine
