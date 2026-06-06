#pragma once
#include "core/debug/i-debug-user-interface.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/application/i-application.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "core/scenes/i-scene-manager.hpp"
#include "core/scenes/i-scene-manager.hpp"
#include "debug/debug-hud.hpp"
#include "engine/config/application-config.hpp"
#include "core/dependency-injection/i-dependency-injector.hpp"
#include "core/debug/i-debug-hud.hpp"
#include "core/window/i-window.hpp"
#include "core/input/i-input-backend.hpp"

#include <memory>

namespace Core {
namespace Debug {
class IDebugUserInterface;
}
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
namespace UserInterface {
class IUserInterface;
}  // namespace UserInterface
}  // namespace Core

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
  virtual void RegisterDependencies() override;

  virtual void Configure(Config::ApplicationConfig& config) override;
  virtual void OnUpdate(float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;

  virtual void OnRender(const Core::Rendering::IRenderer& renderer) const override;
  virtual void Shutdown() override;
  [[nodiscard]] virtual const Config::ApplicationConfig& GetConfig() const override;
  [[nodiscard]] virtual Core::IDependencyInjector& GetInjector() const override;
  [[nodiscard]] virtual Core::Scenes::ISceneManager& GetSceneManager() const override;
  [[nodiscard]] virtual Core::Events::IEventBus& GetEventBus() const override;
  [[nodiscard]] virtual Core::Rendering::IRenderComponentManager&
  GetRenderComponentManager() const override;

 private:
  std::unique_ptr<Core::IDependencyInjector> injector;
  std::shared_ptr<Core::Window::IWindow> window = nullptr;
  std::shared_ptr<Core::Input::IInputBackend> input = nullptr;
  std::shared_ptr<const Core::Rendering::IRenderer> renderer = nullptr;
  std::shared_ptr<Core::Events::IEventBus> eventBus = nullptr;
  std::shared_ptr<Core::Rendering::IRenderComponentManager> renderComponentManager;
  Config::ApplicationConfig config;

  std::unique_ptr<Debug::DebugHUD> debugHUD;

  std::shared_ptr<Core::UserInterface::IUserInterface> userInterface = nullptr;
  std::shared_ptr<Core::Debug::IDebugUserInterface> debugUserInterface = nullptr;
  std::shared_ptr<Core::Debug::IDebugHUD> debugHud = nullptr;
  std::shared_ptr<Core::State::IStateMachine> stateMachine = nullptr;
  std::shared_ptr<Core::Scenes::ISceneManager> sceneManager = nullptr;
};
}  // namespace Engine
