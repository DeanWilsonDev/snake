#include "engine/application.hpp"
#include "raylib-facade/window/raylib-window-facade.hpp"
#include "debug/debug.hpp"
#include "debug/debug-hud.hpp"
#include "debug/i-debug-hud.hpp"
#include "engine/dependency-injection/dependency-injector.hpp"
#include "engine/config/project-settings.hpp"
#include "game/game.hpp"
#include "game/game-state/gameplay-state-machine.hpp"
#include "game/settings/game-settings.hpp"
#include "raylib-facade/input/raylib-input-backend-facade.hpp"
#include "raylib-facade/renderer/raylib-renderer-facade.hpp"
#include "raylib-facade/user-interface/raylib-user-interface-facade.hpp"
#include "core/render-component-2d-manager.hpp"

#include <umbra/log.h>
#include <memory>

class IWindow;

int main(int argc, char* argv[])
{
  constexpr bool debugEnabled = DEBUG_ENABLED;
  Debug::System.SetDebugMode(debugEnabled);

  // Initialize Logging
  Umbra::Logging::Log::init("log.csv", debugEnabled);
  Engine::DependencyInjector injector;

  injector.Register<Platform::Window::IWindow, RaylibFacade::Window::RaylibWindowFacade>();
  injector.Register<Core::IRenderer, RaylibFacade::Renderer::RaylibRendererFacade>();
  injector
      .Register<Platform::Input::IInputBackend, RaylibFacade::Input::RaylibInputBackendFacade>();
  injector.Register<
      UserInterface::IUserInterface,
      RaylibFacade::UserInterface::RaylibUserInterfaceFacade>();
  injector.Register<Core::IStateMachine, Game::GameplayStateMachine>();

  auto hud = std::make_shared<Debug::DebugHUD>();
  injector.RegisterInstance<Debug::IDebugHUD>(hud);

  auto engineConfig = Engine::Config::EngineConfig();

  // 1UP: Need a better way of defining ProjectSettings in the future
  auto projectSettings = Engine::Config::ProjectSettings("Snake");

  const auto renderer2d = injector.Resolve<Core::IRenderer>();
  if (!renderer2d) {
    LOG_FATAL("[Main] Renderer2D could not be instantiated!");
    return -1;
  }

  LOG_TRACE("[Main] Setting up RenderComponent2DManager");
  auto renderManager = Core::RenderComponent2DManager(renderer2d);

  const auto params = Engine::ApplicationParams{
      .injector = injector,
      .engineConfig = engineConfig,
      .projectSettings = projectSettings,
      .renderComponent2dManager = renderManager,
  };

  auto application = Engine::Application(params);

  const std::shared_ptr<Core::IGame> game =
      std::make_shared<Game::Game>(injector, projectSettings, renderManager);
  application.SetGame(game);

  application.Run();
  injector.Teardown();
  return 0;
};
