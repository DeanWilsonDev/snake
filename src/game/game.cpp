//
// Created by Dean Wilson on 14/7/2025.
//

#include "game.hpp"

#include "core/dependency-injector.hpp"
#include "core/math/geometry/rectangle.h"
#include "game-objects/apple.hpp"
#include "game-objects/snake.hpp"
#include "game-state/gameplay-state-machine.hpp"
#include "physics/components/collider-component-2d.hpp"
#include "platform/window/i-window.h"
#include "platform/input/i-input.hpp"
#include "renderer-2d/i-renderer.h"
#include "user-interface/i-user-interface.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "renderer-2d/components/render-component-2d.h"
#include "settings/game-settings.h"
#include "core/i-state-machine.hpp"
#include "game-state/main-menu-state.hpp"

#include <cassert>

namespace Game {

Game::Game(
    Core::DependencyInjector& injector, Engine::Config::ProjectSettings& projectSettings,
    Renderer2D::RenderComponent2DManager& renderManager
)
    : injector(injector), projectSettings(projectSettings), renderManager(renderManager)
{
}
Game::~Game()
{
  if (this->gameplayStateMachine) {
    delete this->gameplayStateMachine;
    this->gameplayStateMachine = nullptr;
  }

  if (this->snake) {
    delete this->snake;
    this->snake = nullptr;
  }

  if (this->apple) {
    delete this->apple;
    this->apple = nullptr;
  }

  if (this->settings) {
    delete this->settings;
    this->settings = nullptr;
  }
}

void Game::Initialize()
{
  // Initialize Settings

  LOG_TRACE("[Game] Initializing Game");
  LOG_TRACE("[Game] Resolving Window");
  const shared_ptr<Platform::Window::IWindow> window =
      injector.Resolve<Platform::Window::IWindow>();

  const auto input = injector.Resolve<Platform::Input::IInput>();
  if (!input) {
    LOG_FATAL("[Game] Failed to initialize Input");
    assert(input);
  }

  LOG_TRACE("[Game] Validating Window");
  assert(window);

  this->settings = new GameSettings{};
  settings->Print();
  settings->SetScreenResolution(window->GetScreenWidth(), window->GetScreenHeight());

  const auto vectorZero = Core::Math::Vector2D::Zero();
  const auto sizeZero = Core::Math::Size2D::Zero();

  // Initialize Snake
  LOG_TRACE("[Game] Setting up Snake GameObject");
  auto snakeSize = static_cast<float>(settings->GetBoxSize());

  auto snakeTransform = Core::Math::Transform2D({100.f, 100.0f}, 0, {snakeSize, snakeSize});

  auto snakeBounds = Core::Math::Geometry::Rectangle(snakeTransform);
  const auto snakeColliderParams = Physics::Components::ColliderComponentParams{
      .transform = snakeTransform, .bounds = snakeBounds
  };

  auto snakeRenderComponent = new Renderer2D::Component::RenderComponent2D(
      snakeTransform.position, snakeTransform.scale, Core::COLOR_GREEN
  );

  auto snakeColliderComponent = new Physics::Components::ColliderComponent2D(snakeColliderParams);

  const auto snakeParams = SnakeParams{
      .renderComponent = *snakeRenderComponent,
      .colliderComponent = *snakeColliderComponent,
      .input = *input,
      .settings = *settings
  };

  this->snake = new Snake(snakeParams);
  LOG_DEBUG("[Game] Snake set to [{}]", static_cast<void*>(&snake));

  // Initialize Apple
  LOG_TRACE("[Game] Setting up Apple GameObject");

  auto appleTransform = Core::Math::Transform2D(vectorZero, 0.0f, sizeZero);

  auto appleBounds = Core::Math::Geometry::Rectangle(appleTransform);
  const auto appleColliderParams = Physics::Components::ColliderComponentParams{
      .transform = appleTransform, .bounds = appleBounds
  };

  auto appleRenderComponent = new Renderer2D::Component::RenderComponent2D(
      appleTransform.position, appleTransform.scale, Core::COLOR_RED
  );

  const auto appleColliderComponent = new Physics::Components::ColliderComponent2D(appleColliderParams);
  const auto appleParams = AppleParams{
      .settings = *settings,
      .colliderComponent = *appleColliderComponent,
      .renderComponent= *appleRenderComponent
  };
  this->apple = new Apple(appleParams);

  LOG_DEBUG(
      "[Game] Apple RenderComponent is Initialized: [{}]", static_cast<void*>(&appleRenderComponent)
  );
  LOG_DEBUG(
      "[Game] Apple ColliderComponent is Initialized: [{}]",
      static_cast<void*>(appleColliderComponent)
  );
  LOG_DEBUG(
      "[Apple] Checking GameSettings is Initialized: [{}]", static_cast<void*>(&this->settings)
  );

  LOG_DEBUG("[Game] Apple set to [{}]", static_cast<void*>(&this->apple));

  const auto renderer = injector.Resolve<Renderer2D::IRenderer>();
  if (!renderer) {
    LOG_FATAL("[Game] Failed to initialize Renderer");
    assert(renderer);
  }

  const auto userInterface = injector.Resolve<UserInterface::IUserInterface>();
  if (!renderer) {
    LOG_FATAL("[Game] Failed to initialize UserInterface");
    assert(userInterface);
  }

  LOG_DEBUG("[Game] Resolving GameplayStateMachine");
  const auto stateMachine = injector.Resolve<Core::IStateMachine>();
  this->gameplayStateMachine = static_cast<GameplayStateMachine*>(stateMachine.get());

  LOG_DEBUG(
      "[Game] GameplayStateMachine set to: [{}]", static_cast<void*>(&this->gameplayStateMachine)
  );

  if (!this->gameplayStateMachine) {
    LOG_FATAL("[Game] Failed to initialize GameplayStateMachine");
    assert(this->gameplayStateMachine);
  }

  Core::IGameState* initialState = new MainMenuState(*this->gameplayStateMachine);
  this->gameplayStateMachine->SetApple(*this->apple);
  this->gameplayStateMachine->SetSnake(*this->snake);

  LOG_DEBUG(
      "[Game] Checking GameSettings on Snake [{}]",
      static_cast<void*>(&this->gameplayStateMachine->GetSnake()->GetGameSettings())
  );

  this->gameplayStateMachine->SetRenderManager(this->renderManager);
  this->gameplayStateMachine->SetRenderer(*renderer);
  this->gameplayStateMachine->SetUserInterface(*userInterface);
  this->gameplayStateMachine->SetInput(*input);
  this->gameplayStateMachine->SetGameSettings(*settings);

  this->gameplayStateMachine->ChangeState(initialState);


  this->renderManager.Register(snakeRenderComponent);
  this->renderManager.Register(appleRenderComponent);
}

void Game::Update(const float deltaTime)
{
  LOG_DEBUG("[Game] Game Update running...");
  this->gameplayStateMachine->Update(deltaTime);
}

void Game::Render()
{
  LOG_DEBUG("[Game] checking RenderManager2D [{}]", static_cast<void*>(&this->renderManager));
  this->renderManager.RenderAll();
}

}  // namespace Game