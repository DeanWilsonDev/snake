#include "snake-game/game-entities/snake.hpp"
#include "engine/events/input/input-action-pressed-event.hpp"
#include "snake-game/settings/snake-game-settings.hpp"
#include "snake-segment.hpp"
#include "core/math/vector-2d.hpp"
#include "core/entities/i-entity-manager.hpp"
#include "engine/spatial/transform-2d.hpp"
#include "core/spatial/components/i-transform-component.hpp"

#include <cmath>
#include <memory>

namespace SnakeGame {

Snake::~Snake() = default;

Snake::Snake(const SnakeParams& snakeParams)
    : entityManager(snakeParams.entityManager)
    , settings(snakeParams.settings)
    , screenWidth(snakeParams.screenWidth)
    , screenHeight(snakeParams.screenHeight)
{
  auto snakeSize = static_cast<float>(settings.boxSize);

  this->transform = Engine::Spatial::Transform2D({100.f, 100.0f}, 0, {snakeSize, snakeSize});
  snakeParams.eventBus.Subscribe<Engine::Events::Input::InputActionPressedEvent>(
      [this](const auto& e) {
        switch (e.action) {
          case Core::Input::Action::MoveLeft:
            this->SetDirection({-1, 0});
            break;
          case Core::Input::Action::MoveRight:
            this->SetDirection({1, 0});
            break;
          case Core::Input::Action::MoveUp:
            this->SetDirection({0, -1});
            break;
          case Core::Input::Action::MoveDown:
            this->SetDirection({0, 1});
            break;
          default:
            break;
        }
      }
  );
}

Snake* Snake::Initialize()
{
  this->size = static_cast<float>(this->settings.boxSize);
  this->speed = this->size * 5.0f;
  this->length = this->settings.defaultSnakeLength;
  this->direction = {1.0f, 0.0f};
  this->grow = false;

  this->CreateBody();

  return this;
}

void Snake::Update(const float deltaTime)
{
  accumulatedDistance += this->speed * deltaTime;

  if (accumulatedDistance >= this->size) {
    this->Move();
    this->CheckIfShouldGrow();

    accumulatedDistance -= this->size;

    this->Teleport();
  }
}

void Snake::SetDirection(Core::Math::Vector2D desiredDirection)
{
  if (desiredDirection.x == -this->direction.x && desiredDirection.y == -this->direction.y) {
    return;
  }
  this->direction = desiredDirection;
}

void Snake::Move() const
{
  Core::Math::Vector2D newPosition = {
      this->head->GetTransformComponent().GetPosition().x + this->direction.x * this->size,
      this->head->GetTransformComponent().GetPosition().y + this->direction.y * this->size,
  };

  newPosition.x = std::roundf(newPosition.x / this->size) * this->size;
  newPosition.y = std::roundf(newPosition.y / this->size) * this->size;

  this->head->Move(newPosition);

  Core::Math::Vector2D nextPosition = newPosition;

  for (int i = 1; i < this->length; i++) {
    if (this->body[i] && this->body[i - 1]) {
      const Core::Math::Vector2D previousPosition =
          this->body[i]->GetTransformComponent().GetPosition();
      this->body[i]->Move(nextPosition);
      nextPosition = previousPosition;
    }
  }
}

void Snake::CreateBody()
{
  for (int i = 0; i < this->length; i++) {
    auto nextSegmentTransform = Engine::Spatial::Transform2D(this->transform);

    nextSegmentTransform.SetPosition(
        Core::Math::Vector2D(
            std::round(
                (this->transform.position.x - this->size * static_cast<float>(i)) * this->size
            ),
            std::round((this->transform.position.y / this->size) * this->size)
        )
    );

    auto params = SnakeSegmentParams{i, &nextSegmentTransform};
    this->CreateSegment(params);
  }  // namespace SnakeGame

  this->head = this->body.front();
}

void Snake::CheckIfShouldGrow()
{
  if (this->grow) {
    const auto params = SnakeSegmentParams{
        this->length, &this->body.back()->GetTransformComponent().GetTransform()
    };

    this->CreateSegment(params);

    this->length++;
    this->grow = false;
  }
}

void Snake::CreateSegment(SnakeSegmentParams params)
{
  auto segment = std::make_unique<SnakeSegment>(params);
  auto bodyPart = this->entityManager.AddEntity(std::move(segment));
  this->body.push_back(static_cast<SnakeSegment*>(bodyPart));
}

void Snake::Teleport() const
{
  // SIDE QUEST: BoundaryWrapSystem
  // Wrapping behaviour should be handled by a dedicated BoundaryWrapSystem in the
  // game-systems layer rather than the Snake querying screen dimensions directly.
  // Snake should have no knowledge of screen bounds — the system takes a list of
  // entities and wraps their positions if they exceed the boundary.

  for (auto& segment : this->body) {
    auto& segmentPosition = segment->GetTransformComponent().GetPosition();
    if (segmentPosition.x > this->screenWidth) {
      segmentPosition.x = 0;
    }
    else if (segmentPosition.x < 0) {
      segmentPosition.x = this->screenWidth;
    }
    else if (segmentPosition.y > this->screenHeight) {
      segmentPosition.y = 0;
    }
    else if (segmentPosition.y < 0) {
      segmentPosition.y = this->screenHeight;
    }
  }
}

Core::Math::Vector2D Snake::GetCenter() const
{
  const auto boxSize = static_cast<float>(this->settings.boxSize);
  return {
      this->head->GetTransformComponent().GetPosition().x + boxSize / 2.0f,
      this->head->GetTransformComponent().GetPosition().y + boxSize / 2.0f,
  };
}

void Snake::SetActive(const bool enabled) const
{
  for (const auto& i : body) {
    i->SetActive(enabled);
  }
  head->SetActive(enabled);
}

void Snake::Destroy()
{
  for (auto& segment : this->body) {
    this->entityManager.RemoveEntity(segment);
  }
  this->body.clear();
  this->head = nullptr;
}
}  // namespace SnakeGame
