#include "snake-application.hpp"
#include "core/input/action-binding-builder.hpp"
#include "core/input/action-value-type.hpp"
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

  inputActions.RegisterAction("MoveVertical", ActionValueType::Axis1D);
  inputActions.RegisterAction("MoveHorizontal", ActionValueType::Axis1D);
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
                        {Core::Input::Bind("MoveVertical")
                             .Axis1D({KeyCode::W, KeyCode::Up}, 1.0f)
                             .Axis1D({KeyCode::S, KeyCode::Down}, -1.0f),
                         Core::Input::Bind("MoveHorizontal")
                             .Axis1D({KeyCode::D, KeyCode::Right}, 1.0f)
                             .Axis1D({KeyCode::A, KeyCode::Left}, -1.0f),
                         Core::Input::Bind("Confirm").Digital({KeyCode::Enter, KeyCode::E}),
                         Core::Input::Bind("Decline").Digital({KeyCode::Escape})}
                    ),
                    .actions = inputActions.All(),
                },
            .debug =
                {
                    .enabled = true,
                    .showDebugHud = true,
                    .showCoreDebugLogs = true, // SIDE QUEST: Hook these settings up to the logger
                    .showClientDebugLogs = true,
                }},
       .project = {.title = "Snake"},
       .game = std::move(snakeSettings)};
}

void SnakeApplication::Initialize()
{
  Engine::Application::Initialize();

  GameplaySceneParams gameplaySceneParams = {
      .eventBus = this->GetEventBus(),
      .renderComponentManager = this->GetRenderComponentManager(),
      .gameSettings = this->GetSnakeSettings(),
      .inputActionRouter = this->GetInputActionRouter(),
      .screenWidth = this->GetConfig().engine.window.GetScreenWidth(),
      .screenHeight = this->GetConfig().engine.window.GetScreenHeight(),
  };

  this->GetSceneManager().Register(
      "Gameplay",
      [gameplaySceneParams]() { return std::make_unique<GameplayScene>(gameplaySceneParams); },
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
