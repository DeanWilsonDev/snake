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
#include "platform/window/iwindow.h"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "renderer-2d/components/render-component-2d.h"
#include "settings/game-settings.h"

#include <cassert>

namespace Game {

Game::Game(
    Core::DependencyInjector& injector, Engine::Config::ProjectSettings& projectSettings,
    Renderer2D::RenderComponent2DManager& renderManager
)
    : injector(injector), projectSettings(projectSettings), renderManager(renderManager)
{
}

void Game::Initialize()
{
  // Initialize Settings

  LOG_TRACE("[Game] Initializing Game");
  LOG_TRACE("[Game] Resolving Window");
  const shared_ptr<Platform::Window::IWindow> window = injector.Resolve<Platform::Window::IWindow>();
  LOG_TRACE("[Game] Validating Window");
  assert(window);

  auto settings = GameSettings{};
  settings.SetScreenResolution(window->GetScreenWidth(), window->GetScreenHeight());

  // Initialize Snake

  auto snakeSize = static_cast<float>(settings.GetBoxSize());

  auto* snakeTransform = new Core::Math::Transform2D({100.f, 100.0f}, 0, {snakeSize, snakeSize});

  auto snakeBounds = Core::Math::Geometry::Rectangle(*snakeTransform);
  const auto snakeColliderParams = Physics::Components::ColliderComponentParams{
      .transform = *snakeTransform, .bounds = snakeBounds
  };

  auto snakeRenderComponent = Renderer2D::Component::RenderComponent2D(
      snakeTransform->scale.x,
      snakeTransform->scale.y,
      snakeTransform->position.x,
      snakeTransform->position.y,
      Core::COLOR_GREEN
  );

  auto snakeColliderComponent = Physics::Components::ColliderComponent2D(snakeColliderParams);

  const auto snakeParams = SnakeParams{
      .renderComponent = snakeRenderComponent,
      .colliderComponent = snakeColliderComponent,
      .settings = settings
  };

  const auto snake = new Snake(snakeParams);
  snake->Initialize();

  // Initialize Apple

  auto* appleTransform =
      new Core::Math::Transform2D(Core::Math::Vector2D::Zero(), 0.0f, Core::Math::Vector2D::Zero());

  auto appleBounds = Core::Math::Geometry::Rectangle(*appleTransform);
  const auto appleColliderParams = Physics::Components::ColliderComponentParams{
      .transform = *appleTransform, .bounds = appleBounds
  };

  auto appleRenderComponent = Renderer2D::Component::RenderComponent2D(
      appleTransform->scale.x,
      appleTransform->scale.y,
      appleTransform->position.x,
      appleTransform->position.y,
      Core::COLOR_RED
  );

  const auto appleColliderComponent =
      new Physics::Components::ColliderComponent2D(appleColliderParams);
  const auto appleParams = AppleParams{.settings = settings, .colliderComponent = *appleColliderComponent};
  const auto apple = new Apple(appleParams);


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

  const auto stateMachine = injector.Resolve<IStateMachine>();
  this->gameplayStateMachine = dynamic_pointer_cast<GameplayStateMachine>(stateMachine);

  if (!this->gameplayStateMachine) {
    LOG_FATAL("[Game] Failed to initialize GameplayStateMachine");
    assert(this->gameplayStateMachine);
  }

  this->gameplayStateMachine->SetApple(*apple);
  this->gameplayStateMachine->InitializeApple();

  this->gameplayStateMachine->SetSnake(*snake);
  this->gameplayStateMachine->InitializeSnake();

  this->gameplayStateMachine->SetRenderManager(renderManager);
  this->gameplayStateMachine->SetRenderer(*renderer);
  this->gameplayStateMachine->SetUI(*userInterface);

}

void Game::Update(float deltaTime)
{
  this->gameplayStateMachine->Update(deltaTime);
}

void Game::Render()
{
  this->renderManager.RenderAll();
}

}  // namespace Game