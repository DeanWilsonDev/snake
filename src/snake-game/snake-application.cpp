#include "snake-application.hpp"
#include "core/input/action-binding-builder.hpp"
#include "core/input/action-value-type.hpp"
#include "core/scenes/scene-base-params.hpp"
#include "core/scenes/scene-lifetime.hpp"
#include "engine/application/application.hpp"
#include "core/scenes/scene-lifetime.hpp"
#include "engine/config/application-config.hpp"
#include "snake-game/settings/snake-game-settings.hpp"
#include "snake-game/game-scenes/gameplay-scene.hpp"
#include <assert.h>
#include <memory>
#include <vector>

namespace SnakeGame {

// 1UP: this could just deserialise a json config file. Amanuensis?
void SnakeApplication::Configure(Engine::Config::ApplicationConfig& config)
{
  auto snakeSettings = std::make_unique<SnakeGameSettings>();

  auto& inputActions = this->GetInputActionSet();

  inputActions.RegisterAction("Up");
  inputActions.RegisterAction("Down");
  inputActions.RegisterAction("Left");
  inputActions.RegisterAction("Right");
  inputActions.RegisterAction("Confirm", ActionValueType::Boolean);
  inputActions.RegisterAction("Decline", ActionValueType::Boolean);

  config =
      {.engine =
           {.window =
                {
                    .width = 500,
                    .height = 500,
                },
            .input =
                {
                    .keyMap = inputActions.BuildKeyMap(
                        {Core::Input::Bind("Up").Digital({KeyCode::W, KeyCode::Up}),
                         Core::Input::Bind("Down").Digital({KeyCode::S, KeyCode::Down}),
                         Core::Input::Bind("Right").Digital({KeyCode::D, KeyCode::Right}),
                         Core::Input::Bind("Left").Digital({KeyCode::A, KeyCode::Left}),
                         Core::Input::Bind("Confirm").Digital({KeyCode::Enter, KeyCode::E}),
                         Core::Input::Bind("Decline").Digital({KeyCode::Escape})}
                    ),
                    .actions = inputActions.All(),
                },
            .debug =
                {
                    .enabled = true,
                    .showDebugHud = true,
                    .showCoreDebugLogs = true,  // SIDE QUEST: Hook these settings up to the logger
                    .showClientDebugLogs = true,
                }},
       .project = {.title = "Snake"},
       .game = std::move(snakeSettings)};
}

void SnakeApplication::Initialize()
{
  Engine::Application::Initialize();

  const auto& gameSettings = this->GetSnakeSettings();
  const int screenWidth = this->GetConfig().engine.window.GetScreenWidth();
  const int screenHeight = this->GetConfig().engine.window.GetScreenHeight();

  this->GetSceneManager().Register(
      "Gameplay",
      [&gameSettings, screenWidth, screenHeight](const Core::Scenes::SceneBaseParams& base) {
        return std::make_unique<GameplayScene>(GameplaySceneParams{
            {base},
            gameSettings,
            screenWidth,
            screenHeight,
        });
      },
      Core::Scenes::SceneLifetime::Transient
  );

  // this->GetSceneManager().Register(
  //     "MainMenu",
  //     Engine::Scenes::SceneManager::MakeSceneFactory<MainMenuScene>(),
  //     SceneLifetime::Transient
  // );

  this->GetSceneManager().SwitchTo("Gameplay");
}

void SnakeApplication::RegisterDependencies()
{
  Engine::Application::RegisterDependencies();

  ///
  /// Register overrides and game-specific dependencies below
  ///
}

const SnakeGame::SnakeGameSettings& SnakeApplication::GetSnakeSettings() const
{
  assert(dynamic_cast<SnakeGame::SnakeGameSettings*>(this->GetConfig().game.get()));
  return static_cast<SnakeGame::SnakeGameSettings&>(*this->GetConfig().game);
}

void SnakeApplication::OnUpdate(const float deltaTime)
{
  Engine::Application::OnUpdate(deltaTime);
}

}  // namespace SnakeGame
