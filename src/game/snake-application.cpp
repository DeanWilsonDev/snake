#include "snake-application.hpp"
#include "engine/application/application.hpp"
#include "raylib-facade/window/raylib-window-facade.hpp"
#include "raylib-facade/renderer/raylib-renderer-facade.hpp"
#include "raylib-facade/input/raylib-input-backend-facade.hpp"
#include "raylib-facade/user-interface/raylib-user-interface-facade.hpp"
#include "platform/input/i-input-backend.hpp"
#include "platform/window/i-window.h"
#include "engine/input/key-code.hpp"
#include "core/user-interface/user-interface-manager.hpp"
#include "game/game-state/gameplay-state-machine.hpp"
#include "engine/config/application-config.hpp"
#include <umbra/log.h>
#include <memory>
#include <vector>

using KeyCode = Engine::Input::KeyCode;

namespace Snake {

void SnakeApplication::Configure(Engine::Config::ApplicationConfig& config)
{
  config = {
      .engine =
          {.window =
               {
                   .width = 500,
                   .height = 500,
               },
           .input =
               {
                   {/* Action::MoveUp    */ std::vector{KeyCode::W, KeyCode::Up},
                    /* Action::MoveLeft  */ std::vector{KeyCode::A, KeyCode::Left},
                    /* Action::MoveDown  */ std::vector{KeyCode::S, KeyCode::Down},
                    /* Action::MoveRight */ std::vector{KeyCode::D, KeyCode::Right},
                    /* Action::Confirm   */ std::vector{KeyCode::Enter}}

               },
           .debug =
               {
                   .enabled = false,
                   .showDebugHud = false,
                   .showDebugLogs = false,  // Show Core Logging
               }},
      .project = {.title = "Snake"},
      .game = {.debug{
          .enabled = false,        // Turn on all Debug options
          .showDebugLogs = false,  // Show Game Related Logging
      }}
  };
}

void SnakeApplication::RegisterDependencies(Core::IDependencyInjector& injector)
{
  // Platform
  injector.Register<Platform::Window::IWindow, RaylibFacade::Window::RaylibWindowFacade>();
  injector.Register<Core::Rendering::IRenderer, RaylibFacade::Renderer::RaylibRendererFacade>();
  injector
      .Register<Platform::Input::IInputBackend, RaylibFacade::Input::RaylibInputBackendFacade>();

  // injector.Register<
  //     UserInterface::IUserInterface,
  //     RaylibFacade::UserInterface::RaylibUserInterfaceFacade>();

  // Game
  injector.Register<Core::State::IStateMachine, Game::GameplayStateMachine>();

  Engine::Application::RegisterDependencies(injector);
}

}  // namespace Snake
