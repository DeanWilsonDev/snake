#include "snake-application.hpp"
#include "core/events/i-event-bus.hpp"
#include "engine/application/application.hpp"
#include "engine/events/event-bus.hpp"
#include "raylib-facade/window/raylib-window-facade.hpp"
#include "raylib-facade/renderer/raylib-renderer-facade.hpp"
#include "raylib-facade/input/raylib-input-backend-facade.hpp"
#include "platform/input/i-input-backend.hpp"
#include "platform/window/i-window.hpp"
#include "engine/input/key-code.hpp"
#include "core/user-interface/user-interface-manager.hpp"
#include "snake-game/game-state/gameplay-state-machine.hpp"
#include "engine/config/application-config.hpp"
#include <vector>

using KeyCode = Engine::Input::KeyCode;

namespace SnakeGame {

void SnakeApplication::Initialize()
{
  Engine::Application::Initialize();
}

// 1UP: this could just deserialise a json config file. Amanuensis?
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

void SnakeApplication::RegisterDependencies()
{
  Engine::Application::RegisterDependencies();

  // Platform
  this->GetInjector()
      .Register<Platform::Window::IWindow, RaylibFacade::Window::RaylibWindowFacade>();
  this->GetInjector()
      .Register<Core::Rendering::IRenderer, RaylibFacade::Renderer::RaylibRendererFacade>();
  this->GetInjector()
      .Register<Platform::Input::IInputBackend, RaylibFacade::Input::RaylibInputBackendFacade>();

  // injector.Register<
  //     UserInterface::IUserInterface,
  //     RaylibFacade::UserInterface::RaylibUserInterfaceFacade>();

  // Game
  this->GetInjector().Register<Core::State::IStateMachine, SnakeGame::GameplayStateMachine>();

  this->GetInjector().RegisterSingleton<Core::Events::IEventBus, Engine::Events::EventBus>();
}

}  // namespace SnakeGame
