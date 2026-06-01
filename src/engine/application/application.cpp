#include "application.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "core/scenes/i-scene-manager.hpp"
#include "engine/config/project-settings.hpp"
#include "core/color/color.hpp"
#include "core/user-interface/user-interface-manager.hpp"
#include "core/user-interface/i-user-interface-manager.hpp"
#include "engine/config/application-config.hpp"
#include "engine/dependency-injection/dependency-injector.hpp"
#include "core/debug/i-debug-hud.hpp"
#include "debug/debug.hpp"
#include "debug/debug-hud.hpp"
#include "core/rendering/i-renderer.hpp"
#include "engine/scenes/scene-manager.hpp"
#include "engine/utils/string-utils.hpp"
#include "platform/input/i-input-backend.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "user-interface/i-user-interface.hpp"
#include "core/dependency-injection/i-dependency-injector.hpp"
#include "core/logging/log.hpp"
#include "core/state/i-state-machine.hpp"
#include "core/events/i-event-bus.hpp"
#include "engine/events/event-bus.hpp"
#include "platform/input/i-input-backend.hpp"
#include "platform/window/i-window.hpp"

#include "raylib-facade/window/raylib-window-facade.hpp"
#include "raylib-facade/renderer/raylib-renderer-facade.hpp"
#include "raylib-facade/input/raylib-input-backend-facade.hpp"

#include <memory>
#include <cassert>
#include <chrono>
#include "platform/window/i-window.hpp"

namespace Engine {

Application::Application()
    : injector(std::make_unique<DependencyInjector>()) {

    };

Application::~Application() = default;

void Application::Initialize()
{

  const auto& config = this->GetConfig();

  const auto& debug = config.engine.debug;
  Debug::System.SetDebugMode(debug.enabled);

  LOG_INIT("log.csv", debug.enabled);


  LOG_CORE_TRACE("[Application] Initializing");
  this->window = this->injector->Resolve<Platform::Window::IWindow>();
  this->renderer = this->injector->Resolve<Core::Rendering::IRenderer>();
  this->stateMachine = this->injector->Resolve<Core::State::IStateMachine>();
  this->input = this->injector->Resolve<Platform::Input::IInputBackend>();
  this->userInterface = this->injector->Resolve<UserInterface::IUserInterface>();
  this->eventBus = this->injector->Resolve<Core::Events::IEventBus>();
  this->renderComponentManager =
      this->injector->Resolve<Core::Rendering::IRenderComponentManager>();
  Debug::System.SetActiveDebugHUD(this->injector->Resolve<Core::Debug::IDebugHUD>());

  LOG_CORE_TRACE("[Application] Window set to {}", static_cast<void*>(&window));
  LOG_CORE_TRACE("[Application] Renderer set to {}", static_cast<void*>(&renderer));
  LOG_CORE_TRACE("[Application] StateMachine set to {}", static_cast<void*>(&stateMachine));
  LOG_CORE_TRACE("[Application] Input set to {}", static_cast<void*>(&input));
  LOG_CORE_TRACE("[Application] UserInterface set to {}", static_cast<void*>(&userInterface));
  LOG_CORE_TRACE("[Application] EventBus set to {}", static_cast<void*>(&eventBus));
  LOG_CORE_TRACE("[Application] DebugHUD set to {}", static_cast<void*>(&debugHud));

  LOG_CORE_TRACE("[Application] Validating Dependencies");
  assert(this->window);
  assert(this->renderer);
  assert(this->stateMachine);
  assert(this->input);
  assert(this->userInterface);
  assert(this->eventBus);



  LOG_CORE_TRACE("[Application] Beginning Application");
  std::string title = config.project.title;

  LOG_CORE_INFO("[Application] Starting Game: {}", title);

  char* windowTitle = StringUtils::DuplicateAsCString(title);

  LOG_CORE_DEBUG("[Application] Window Title set: {}", windowTitle);
  assert(windowTitle);

  if (!this->window) {
    LOG_CORE_FATAL("[Application] Failed to initialize window");
    assert(this->window);
  }
  this->window->CreateWindow(config.engine.window.width, config.engine.window.height, windowTitle);
  this->window->SetTargetFPS(config.engine.window.targetFPS);
}

void Application::RegisterDependencies()
{
  // Raylib Dependencies as defaults:

  // Platform
  this->GetInjector()
      .Register<Platform::Window::IWindow, RaylibFacade::Window::RaylibWindowFacade>();
  this->GetInjector()
      .Register<Core::Rendering::IRenderer, RaylibFacade::Renderer::RaylibRendererFacade>();
  this->GetInjector()
      .Register<Platform::Input::IInputBackend, RaylibFacade::Input::RaylibInputBackendFacade>();

  // Reaper: Not sure if i need this
  // injector.Register<
  //     UserInterface::IUserInterface,
  //     RaylibFacade::UserInterface::RaylibUserInterfaceFacade>();

  injector->Register<
      Core::UserInterface::IUserInterfaceManager,
      Core::UserInterface::UserInterfaceManager>();

  // Rendering
  injector
      ->Register<Core::Rendering::IRenderComponentManager, Renderer2D::RenderComponent2DManager>();

  // Scene Management
  injector->Register<Core::Scenes::ISceneManager, Engine::Scenes::SceneManager>();

  // Debug
  auto hud = std::make_shared<Debug::DebugHUD>();
  this->injector->RegisterInstance<Core::Debug::IDebugHUD>(hud);

  // Events
  this->injector->RegisterSingleton<Core::Events::IEventBus, Engine::Events::EventBus>();
}

void Application::Run()
{
  this->Configure(this->config);

  this->RegisterDependencies();

  this->Initialize();
  LOG_CORE_DEBUG("[Application] Window Should Close {}", this->window->ShouldClose());

  std::chrono::time_point lastTime = std::chrono::high_resolution_clock::now();
  LOG_CORE_TRACE("[Application] Beginning application loop");
  while (!this->window->ShouldClose()) {
    // Calculate DeltaTime
    std::chrono::time_point currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - lastTime;
    const float deltaTime = elapsedTime.count();
    lastTime = currentTime;

    this->OnUpdate(deltaTime);

    this->OnDebugUpdate();

    this->OnRender(*this->renderer);

    this->OnDebugRender();

    // FINISH:
    this->renderer->EndDrawing();
  }
  Shutdown();
  this->injector->Teardown();
}

void Application::Configure(Config::ApplicationConfig&) {}
void Application::OnUpdate(float) {}

void Application::OnDebugUpdate() const {}

void Application::OnRender(const Core::Rendering::IRenderer& renderer) const
{
  // RENDERING:
  renderer.BeginDrawing();
  renderer.ClearBackground(Core::Color::Black);
  this->renderComponentManager->OnRender(renderer);
}

void Application::OnDebugRender() const {}

void Application::Shutdown()
{
  this->window->CloseWindow();
}

const Config::ApplicationConfig& Application::GetConfig() const
{
  return this->config;
}

Core::IDependencyInjector& Application::GetInjector() const
{
  return *this->injector;
}

Core::Scenes::ISceneManager& Application::GetSceneManager() const
{
  return *this->sceneManager;
}

Core::Events::IEventBus& Application::GetEventBus() const
{
  return *this->eventBus;
}

Core::Rendering::IRenderComponentManager& Application::GetRenderComponentManager() const
{
  return *this->renderComponentManager;
}

}  // namespace Engine
