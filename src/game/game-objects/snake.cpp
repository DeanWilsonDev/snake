#include "game/game-objects/snake.hpp"
#include "game/settings/game-settings.h"
#include "log.h"
#include "raylib.h"
#include "snake-segment.hpp"
#include "platform/input/key-codes.hpp"
#include "platform/input/i-input.hpp"

namespace Game {

Snake::~Snake() = default;

Snake::Snake(const SnakeParams& snakeParams)
    : input(snakeParams.input), settings(snakeParams.settings)
{
  LOG_DEBUG("[Snake] Checking Input is Initialized: [{}]", static_cast<void*>(&this->input));
  LOG_DEBUG(
      "[Snake] Checking GameSettings is Initialized: [{}]", static_cast<void*>(&this->settings)
  );
}

Snake* Snake::Initialize()
{
  LOG_TRACE("[Snake] Initializing Snake");
  LOG_DEBUG("[Snake] Checking Input is Initialized: [{}]", static_cast<void*>(&this->input));
  LOG_DEBUG(
      "[Snake] Checking GameSettings is Initialized: [{}]", static_cast<void*>(&this->settings)
  );

  this->size = static_cast<float>(this->settings.GetBoxSize());

  this->speed = this->size * 5.0f;
  this->length = this->settings.defaultSnakeLength;
  this->direction = {1.0f, 0.0f};
  this->grow = false;

  LOG_TRACE("[Snake] Finished Initializing Snake");
  return this;
}

void Snake::Update(const float deltaTime)
{
  LOG_TRACE("[Snake] Snake Update Begin");
  Core::Math::Vector2D newDirection = this->direction;

  // Side Quest: [Snake] Input should really be handled by the gameplay state rather than the
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
  LOG_TRACE("[Snake] Begin calling Move function");
  Core::Math::Vector2D previousPosition = this->head->transform->GetPosition();
  Core::Math::Vector2D nextPosition = previousPosition;

  for (int i = 1; i < this->length; i++) {
    if (this->body[i] && this->body[i - 1]) {
      previousPosition = this->body[i]->transform->GetPosition();
      this->body[i]->Move(nextPosition);
      nextPosition = previousPosition;
    }
  }

  Core::Math::Vector2D newPosition = {
      this->head->transform->GetPosition().x + this->direction.x * this->size,
      this->head->transform->GetPosition().y + this->direction.y * this->size,
  };

  LOG_DEBUG("[Snake] Direction: {}", this->direction.ToString());
  LOG_DEBUG("[Snake] Head Position: {}", this->head->transform->GetPosition().ToString());
  LOG_DEBUG("[Snake] New Position: {}", newPosition.ToString());

  newPosition.x = std::roundf(newPosition.x / this->size) * this->size;
  newPosition.y = std::roundf(newPosition.y / this->size) * this->size;

  this->head->Move(newPosition);
}

void Snake::CreateHead(Core::Components::TransformComponent2D& transform)
{
  const auto snakeSegmentParams = SnakeSegmentParams{
      .index = 0,
      .transform = &transform,
  };

  this->head = new SnakeSegment(snakeSegmentParams);
  this->body.push_back(this->head);
}

void Snake::CreateBody(Core::Components::TransformComponent2D& headTransformComponent)
{
  for (int i = 1; i < this->length; i++) {
    auto* nextSegmentTransform =
        new Core::Components::TransformComponent2D(&headTransformComponent);
    nextSegmentTransform->GetPosition().x =
        headTransformComponent.GetPosition().x - this->size * static_cast<float>(i);
    LOG_DEBUG(
        "Head Transform ({},{}), Next Segment Transform ({},{})",
        headTransformComponent.GetPosition().x,
        headTransformComponent.GetPosition().y,
        nextSegmentTransform->GetPosition().x,
        nextSegmentTransform->GetPosition().y
    );
    this->body.push_back(new SnakeSegment(
        {.index = i,
         .transform = nextSegmentTransform,
         .colliderComponent = nullptr,
         .renderComponent = nullptr}
    ));
  }
}

void Snake::CheckIfShouldGrow()
{
  LOG_TRACE("[Snake] Checking if Snake should grow {}", this->grow);
  if (this->grow) {
    const auto newSegmentTransformComponent = this->body.back()->transform;

    const auto segmentParams = SnakeSegmentParams{
        .index = this->length,
        .transform = newSegmentTransformComponent,
        .colliderComponent = nullptr,
        .renderComponent = nullptr
    };

    const auto segment = new SnakeSegment(segmentParams);
    this->body.push_back(segment);
    this->length++;
    this->grow = false;

    LOG_TRACE("[Snake] Snake Grew Successfully");
  }
}

void Snake::Teleport() const
{
  const auto screenWidth = static_cast<float>(this->settings.GetScreenWidth());
  const auto screenHeight = static_cast<float>(this->settings.GetScreenHeight());

  for (const auto segment : this->body) {
    if (auto segmentPosition = segment->transform->GetPosition(); segmentPosition.x > screenWidth) {
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
void Snake::SetEnabled(const bool enabled) const
{
  for (const auto& i : body) {
    i->GetRendererComponent2D()->SetEnabled(enabled);
    i->SetActive(enabled);
  }
  head->GetRendererComponent2D()->SetEnabled(enabled);
  head->SetActive(enabled);
}

void Snake::Destroy()
{
  if (!body.empty() && body.front() == head) {
    body.pop_front();
  }

  for (const auto segment : body) {
    if (segment) {
      int index = segment->index;
      LOG_TRACE("[Snake] Deleting segment with index: {}", index);
      delete segment;
      LOG_TRACE("[Snake] Successfully deleted segment with index: {}", index);
    }
    else {
      LOG_ERROR("[Snake] Found null segment in body!");
    }
  }

  this->body.clear();

  if (head) {
    LOG_DEBUG("[Snake] Deleting head at address: {}", static_cast<void*>(&this->head));
    delete this->head;
    LOG_DEBUG("[Snake] Setting head to nullptr");
    this->head = nullptr;
    LOG_DEBUG("[Snake] Head successfully destroyed");
  }
  else {
    LOG_DEBUG("[Snake] Found null segment in head!");
  }
}
}  // namespace Game
