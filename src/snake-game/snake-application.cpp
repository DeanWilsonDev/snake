#include "snake-application.hpp"
#include "engine/application/application.hpp"
#include "engine/input/key-code.hpp"
#include "engine/config/application-config.hpp"
#include <vector>

using KeyCode = Engine::Input::KeyCode;

namespace SnakeGame {

void SnakeApplication::Initialize()
{
  Engine::Application::Initialize();


  this->GetSceneManager();

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

  ///
  /// Register Overrides Below
  ///
}

}  // namespace SnakeGame
