//
// Created by Dean Wilson on 14/7/2025.
//

#include "game.hpp"

#include "core/math/geometry/rectangle.h"
#include "game-objects/apple.hpp"
#include "game-objects/snake.hpp"
#include "physics/components/collider-component-2d.hpp"
#include "renderer-2d/components/render-component-2d.h"
#include "settings/game-settings.h"

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

  auto settings = GameSettings{};

  // Initialize Snake

  auto snakeSize = static_cast<float>(settings.GetBoxSize());

  auto* snakeTransform = new Core::Math::Transform2D(
    {100.f, 100.0f},
    0,
    {snakeSize, snakeSize}
    );

  auto snakeBounds = Core::Math::Geometry::Rectangle(snakeTransform);
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

  auto* appleBounds = new Core::Math::Geometry::Rectangle(appleTransform);
  const auto appleColliderParams = Physics::Components::ColliderComponentParams{
      .transform = *appleTransform, .bounds = *appleBounds
  };

  auto appleRenderComponent = Renderer2D::Component::RenderComponent2D(
      appleTransform->scale.x,
      appleTransform->scale.y,
      appleTransform->position.x,
      appleTransform->position.y,
      Core::COLOR_RED
  );

  const auto appleColliderComponent = new Physics::Components::ColliderComponent2D(appleColliderParams);
  const auto appleParams = AppleParams{.colliderComponent = *appleColliderComponent};
  const auto apple = new Apple(appleParams);
}

void Game::Update(float deltaTime) {}

void Game::Render() {}

}  // namespace Game