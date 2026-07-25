#pragma once
#include "core/debug/i-debug-user-interface.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/application/i-application.hpp"
#include "core/input/i-input-system.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "core/scenes/i-scene-manager.hpp"
#include "core/scenes/i-scene-manager.hpp"
#include "core/systems/i-system.hpp"
#include "debug/debug-hud.hpp"
#include "engine/config/application-config.hpp"
#include "core/dependency-injection/i-dependency-injector.hpp"
#include "core/debug/i-debug-hud.hpp"
#include "core/window/i-window.hpp"
#include "core/input/i-input-backend.hpp"
#include "core/input/action-set.hpp"

#include <memory>
#include <vector>

namespace Core::Input {
class ActionRouter;
}

namespace Core::Debug {
class IDebugUserInterface;
}

namespace Core::Scenes {
class ISceneManager;
}

namespace Core::State {
class IStateMachine;
}  // namespace Core::State

namespace Core::State {
class IGameState;
}  // namespace Core::State

namespace Core::Rendering {
class RenderComponent2DManager;
}  // namespace Core::Rendering

namespace Core::Rendering {
class IRenderer;
}  // namespace Core::Rendering

namespace Core::UserInterface {
class IUserInterface;
}  // namespace Core::UserInterface

namespace Platform::Input {
class IInputBackend;
}

namespace Platform::Window {
class IWindow;
}  // namespace Platform::Window

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
  virtual void RegisterDependencies() override;
  virtual void Configure(Config::ApplicationConfig& config) override;
  virtual void Initialize() override;
  virtual void OnUpdate(const float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;
  virtual void OnRender(const Core::Rendering::IRenderer& renderer) const override;
  virtual void Shutdown() override;
  virtual void RegisterSystem(const std::shared_ptr<Core::Systems::ISystem>& system) override;

  [[nodiscard]] virtual const Config::ApplicationConfig& GetConfig() const override;
  [[nodiscard]] virtual Core::IDependencyInjector& GetInjector() const override;
  [[nodiscard]] virtual Core::Scenes::ISceneManager& GetSceneManager() const override;
  [[nodiscard]] virtual const Core::Input::ActionSet& GetInputActionSet() const override;
  [[nodiscard]] virtual Core::Input::ActionSet& GetInputActionSet() override;
  [[nodiscard]] virtual Core::Input::ActionRouter& GetInputActionRouter() override;
  [[nodiscard]] virtual Core::Events::IEventBus& GetEventBus() const override;
  [[nodiscard]] virtual Core::Rendering::IRenderComponentManager&
  GetRenderComponentManager() const override;

 private:
  std::unique_ptr<Core::IDependencyInjector> injector;
  std::shared_ptr<Core::Window::IWindow> window = nullptr;
  std::shared_ptr<Core::Input::IInputBackend> inputBackend = nullptr;
  std::shared_ptr<const Core::Rendering::IRenderer> renderer = nullptr;
  std::shared_ptr<Core::Events::IEventBus> eventBus = nullptr;
  std::shared_ptr<Core::Rendering::IRenderComponentManager> renderComponentManager;
  Config::ApplicationConfig config;

  std::shared_ptr<Core::UserInterface::IUserInterface> userInterface = nullptr;
  std::shared_ptr<Core::Debug::IDebugUserInterface> debugUserInterface = nullptr;
  std::shared_ptr<Core::Debug::IDebugHUD> debugHud = nullptr;
  std::shared_ptr<Core::State::IStateMachine> stateMachine = nullptr;
  std::shared_ptr<Core::Input::IInputSystem> inputSystem = nullptr;
  std::shared_ptr<Core::Scenes::ISceneManager> sceneManager = nullptr;
  std::vector<std::shared_ptr<Core::Systems::ISystem>> systems;
  Core::Input::ActionSet inputActionSet;
};
}  // namespace Engine
