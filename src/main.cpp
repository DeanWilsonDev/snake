#include "engine/application.h"
#include "raylib-facade/window/raylib-window-facade.hpp"
#include "log.h"
#include "core/dependency-injector.hpp"
#include "engine/config/project-settings.hpp"
#include "game/game-state/gameplay-state-machine.hpp"
#include "game/settings/game-settings.h"
#include "raylib-facade/input/raylib-input-facade.hpp"
#include "raylib-facade/renderer/raylib-renderer-facade.hpp"
#include "raylib-facade/user-interface/raylib-user-interface-facade.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"

class IWindow;

int main(int argc, char* argv[])
{
  // Initialize Logging
  constexpr bool debugEnabled = DEBUG_ENABLED;
  Umbra::Logging::Log::init(debugEnabled);
  Core::DependencyInjector injector;

  injector.Register<Platform::Window::IWindow, RaylibFacade::Window::RaylibWindowFacade>();
  injector.Register<Renderer2D::IRenderer, RaylibFacade::Renderer::RaylibRendererFacade>();
  injector.Register<Platform::Input::IInput, RaylibFacade::Input::RaylibInputFacade>();
  injector.Register<
      UserInterface::IUserInterface,
      RaylibFacade::UserInterface::RaylibUserInterfaceFacade>();
  injector.Register<Core::IStateMachine, Game::GameplayStateMachine>();

  // Platform::Input::InputManager::SetBackend(std::make_unique<RaylibFacade::Input::RaylibInputFacade>());
  // Platform::Window::WindowManager::SetBackend(std::make_unique<RaylibFacade::Window::RaylibWindowFacade>());
  // UserInterface::UserInterfaceManager::SetBackend(std::make_unique<RaylibFacade::UserInterface::RaylibUserInterfaceFacade>());

  auto engineConfig = Engine::Config::EngineConfig();

  // 1UP: Need a better way of defining ProjectSettings in the future
  auto projectSettings = Engine::Config::ProjectSettings("Snake");

  const auto renderer2d = injector.Resolve<Renderer2D::IRenderer>();

  Renderer2D::RenderComponent2DManager renderManager =
      Renderer2D::RenderComponent2DManager(renderer2d);

  const auto params = Engine::ApplicationParams{
      .injector = injector,
      .engineConfig = engineConfig,
      .projectSettings = projectSettings,
      .renderComponent2dManager = renderManager
  };

  auto application = Engine::Application(params);

  application.Run();
  injector.Teardown();
  return 0;
};
