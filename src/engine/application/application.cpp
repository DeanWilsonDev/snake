#include "application.hpp"
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
#include "platform/input/i-input-backend.hpp"
#include "user-interface/i-user-interface.hpp"
#include "core/i-dependency-injector.hpp"
#include "core/logging/log.hpp"

#include <memory>
#include <cassert>
#include <string.h>
#include <chrono>
#include "game/game-state/gameplay-state-machine.hpp"
#include "platform/window/i-window.hpp"
#include "core/i-game.hpp"
#include "engine/game/game.hpp"
#include <utility>

namespace Engine {

Application::Application(std::unique_ptr<Core::IGame> game)
    : game(std::move(game)), injector(std::make_unique<DependencyInjector>()) {

    };

Application::~Application() = default;

void Application::Initialize()
{
  LOG_CORE_TRACE("[Application] Initializing");
  this->window = this->injector->Resolve<Platform::Window::IWindow>();
  this->renderer = this->injector->Resolve<Core::Rendering::IRenderer>();
  this->stateMachine = this->injector->Resolve<Core::State::IStateMachine>();
  this->input = this->injector->Resolve<Platform::Input::IInputBackend>();
  this->userInterface = this->injector->Resolve<UserInterface::IUserInterface>();
  Debug::System.SetActiveDebugHUD(this->injector->Resolve<Core::Debug::IDebugHUD>());

  LOG_CORE_TRACE("[Application] Window set to {}", static_cast<void*>(&window));
  LOG_CORE_TRACE("[Application] Renderer set to {}", static_cast<void*>(&renderer));
  LOG_CORE_TRACE("[Application] StateMachine set to {}", static_cast<void*>(&stateMachine));
  LOG_CORE_TRACE("[Application] Input set to {}", static_cast<void*>(&input));
  LOG_CORE_TRACE("[Application] UserInterface set to {}", static_cast<void*>(&userInterface));
  LOG_CORE_TRACE("[Application] DebugHUD set to {}", static_cast<void*>(&debugHud));

  LOG_CORE_TRACE("[Application] Validating Dependencies");
  assert(this->window);
  assert(this->renderer);
  assert(this->stateMachine);
  assert(this->input);
  assert(this->userInterface);

  const auto& config = this->GetConfig();

  const auto& debug = config.engine.debug;
  Debug::System.SetDebugMode(debug.enabled);

  LOG_INIT("log.csv", debug.enabled);

  LOG_CORE_TRACE("[Application] Beginning Application");
  std::string title = config.project.title;

  LOG_CORE_INFO("[Application] Starting Game: {}", title);

  // TODO: Extract this into a utils function
#if defined(_WIN32)
  char* windowTitle = _strdup(title);
#else
  char* windowTitle = strdup(title.c_str());
#endif

  LOG_CORE_DEBUG("[Application] Window Title set: {}", windowTitle);
  assert(windowTitle);

  if (!this->window) {
    LOG_CORE_FATAL("[Application] Failed to initialize window");
    assert(this->window);
  }
  this->window->CreateWindow(config.engine.window.width, config.engine.window.height, windowTitle);
  this->window->SetTargetFPS(config.engine.window.targetFPS);
}

void Application::RegisterDependencies(Core::IDependencyInjector& injector)
{
  injector.Register<
      Core::UserInterface::IUserInterfaceManager,
      Core::UserInterface::UserInterfaceManager>();

  // Debug
  auto hud = std::make_shared<Debug::DebugHUD>();
  injector.RegisterInstance<Core::Debug::IDebugHUD>(hud);
}

void Application::SetGame(std::unique_ptr<Core::IGame> game)
{
  LOG_CORE_TRACE("[Application] Setting Game to {}", static_cast<void*>(&game));
  this->game = std::move(game);
  if (this->game) {
    this->game->Initialize();
  }
}

void Application::Run()
{
  this->Configure(this->config);

  this->RegisterDependencies(*this->injector);

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

    this->Update(deltaTime);

    this->DebugUpdate();

    this->Render();

    this->DebugRender();

    // FINISH:
    this->renderer->EndDrawing();
  }
  Shutdown();
  this->injector->Teardown();
}

void Application::Update(float deltaTime)
{
  if (this->game) {
    this->game->Update(deltaTime);
  }
}

void Application::DebugUpdate()
{
  // DEBUGGING:
  if (Debug::System.GetDebugMode()) {
    this->game->DebugUpdate();
  }
}

void Application::Render()
{
  // RENDERING:
  this->renderer->BeginDrawing();
  this->renderer->ClearBackground(Core::Color::Black);
  // MAIN QUEST: Sort out who is rendering and updating etc
  if (game) {
    this->game->Render();
  }
}
void Application::DebugRender()
{
  if (this->GetConfig().engine.debug.showDebugHud) {
    // Main Quest: [DebugRenderer] Wire up DebugHUD to game rendering
    this->game->DebugRender();
  }
}

void Application::Shutdown()
{
  this->window->CloseWindow();
}

}  // namespace Engine
