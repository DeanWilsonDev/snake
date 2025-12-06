#include "game/game-objects/snake.hpp"
#include "game/settings/game-settings.h"
#include "snake-segment.hpp"
#include "platform/input/key-codes.hpp"
#include "platform/input/i-input.hpp"
#include "core/math/vector-2d.hpp"
#include "core/math/transform-2d.hpp"

#include <cmath>
#include <utility>

namespace Game {

Snake::~Snake() = default;

Snake::Snake(const SnakeParams& snakeParams)
    : input(snakeParams.input), settings(snakeParams.settings)
{

  auto snakeSize = static_cast<float>(settings.GetBoxSize());

  this->transform = Core::Math::Transform2D({100.f, 100.0f}, 0, {snakeSize, snakeSize});
}

Snake* Snake::Initialize()
{
  this->size = static_cast<float>(this->settings.GetBoxSize());

  this->speed = this->size * 5.0f;
  this->length = this->settings.defaultSnakeLength;
  this->direction = {1.0f, 0.0f};
  this->grow = false;

  this->CreateHead();
  this->CreateBody();


  return this;
}

void Snake::Update(const float deltaTime)
{
  Core::Math::Vector2D newDirection = this->direction;

  // SIDE QUEST: [Snake] Input should really be handled by the gameplay state rather than the
  // gameobject
  if (this->direction.y != 0 && !directionChanged) {
    if (this->input.IsKeyPressed(Platform::Input::KEY_A)) {
      newDirection = {-1.0f, 0.0f};
    }
    if (this->input.IsKeyPressed(Platform::Input::KEY_D)) {
      newDirection = {1.0f, 0.0f};
    }
  }
  if (this->direction.x != 0 && !directionChanged) {
    if (this->input.IsKeyPressed(Platform::Input::KEY_S)) {
      newDirection = {0.0f, 1.0f};
    }
    if (this->input.IsKeyPressed(Platform::Input::KEY_W)) {
      newDirection = {0.0f, -1.0f};
    }
  }

  if (newDirection.x != this->direction.x && newDirection.y != this->direction.y) {
    directionChanged = true;
    this->direction = newDirection;
  }
  accumulatedDistance += this->speed * deltaTime;

  if (accumulatedDistance >= this->size) {
    this->Move();
    this->CheckIfShouldGrow();

    accumulatedDistance -= this->size;

    if (directionChanged) {
      directionChanged = false;
    }

    this->Teleport();
  }
}

void Snake::Move() const
{

  Core::Math::Vector2D newPosition = {
      this->head->transform->GetPosition().x + this->direction.x * this->size,
      this->head->transform->GetPosition().y + this->direction.y * this->size,
  };

  newPosition.x = std::roundf(newPosition.x / this->size) * this->size;
  newPosition.y = std::roundf(newPosition.y / this->size) * this->size;

  this->head->Move(newPosition);

  Core::Math::Vector2D nextPosition = newPosition;

  for (int i = 1; i < this->length; i++) {
    if (this->body[i] && this->body[i - 1]) {
      const Core::Math::Vector2D previousPosition = this->body[i]->transform->GetPosition();
      this->body[i]->Move(nextPosition);
      nextPosition = previousPosition;
    }
  }

}

void Snake::CreateHead()
{

  const auto snakeSegmentParams = SnakeSegmentParams{
      .index = 0,
      .initialTransform = this->transform,
  };

  this->head = new SnakeSegment(snakeSegmentParams);
  this->body.push_back(this->head);
}

void Snake::CreateBody()
{
  for (int i = 1; i < this->length; i++) {
    auto nextSegmentTransform = Core::Math::Transform2D(this->transform);

    nextSegmentTransform.position.x = std::round(
        (this->transform.position.x - this->size * static_cast<float>(i) / this->size) * this->size
    );
    nextSegmentTransform.position.y =
        std::round((this->transform.position.y / this->size) * this->size);


    auto params = SnakeSegmentParams{.index = i, .initialTransform = nextSegmentTransform};
    this->body.push_back(new SnakeSegment(params));
  }
}

void Snake::CheckIfShouldGrow()
{
  if (this->grow) {
    Core::Math::Transform2D newSegmentTransformComponent =
        std::move(this->body.back()->transform->GetTransform());

    const auto segmentParams = SnakeSegmentParams{
        .index = this->length, .initialTransform = std::move(newSegmentTransformComponent)
    };

    const auto segment = new SnakeSegment(segmentParams);
    this->body.push_back(segment);
    this->length++;
    this->grow = false;

  }
}

void Snake::Teleport() const
{
  const auto screenWidth = static_cast<float>(this->settings.GetScreenWidth());
  const auto screenHeight = static_cast<float>(this->settings.GetScreenHeight());

  for (const auto* segment : this->body) {
    auto& segmentPosition = segment->transform->GetPosition();
    if (segmentPosition.x > screenWidth) {
      segmentPosition.x = 0;
    }
    else if (segmentPosition.x < 0) {
      segmentPosition.x = screenWidth;
    }
    else if (segmentPosition.y > screenHeight) {
      segmentPosition.y = 0;
    }
    else if (segmentPosition.y < 0) {
      segmentPosition.y = screenHeight;
    }
  }
}

Core::Math::Vector2D Snake::GetCenter() const
{
  const auto boxSize = static_cast<float>(this->settings.GetBoxSize());
  return {
      this->head->transform->GetPosition().x + boxSize / 2.0f,
      this->head->transform->GetPosition().y + boxSize / 2.0f,
  };
}

/**
 * @brief Enables or disables the Snake entity, including its head and body segments.
 *
 * This method sets the enabled state of the snake's rendering and active state
 * for both the head and each individual body segment.
 *
 * @param enabled A boolean value indicating whether the snake should be enabled
 * (true) or disabled (false).
 */
void Snake::SetActive(const bool enabled) const
{
  for (const auto& i : body) {
    i->SetActive(enabled);
  }
  head->SetActive(enabled);
}

void Snake::Destroy()
{
  if (!body.empty() && body.front() == head) {
    body.pop_front();
  }

  for (const auto segment : body) {
    if (segment) {
      delete segment;
    }
    else {
    }
  }

  this->body.clear();

  if (head) {
    delete this->head;
    this->head = nullptr;
  }
  else {
  }
}
}  // namespace Game
