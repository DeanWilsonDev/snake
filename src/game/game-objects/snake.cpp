#include "game/game-objects/snake.hpp"
#include "game/settings/game-settings.h"
#include "log.h"
#include "snake-segment.hpp"
#include "platform/input/key-codes.hpp"
#include "platform/input/i-input.hpp"

namespace Game {

Snake::~Snake() = default;

Snake::Snake(const SnakeParams& snakeParams)
    : renderComponent(snakeParams.renderComponent)
    , colliderComponent(snakeParams.colliderComponent)
    , input(snakeParams.input)
    , settings(snakeParams.settings)
{
  Initialize();
}

Snake* Snake::Initialize()
{
  LOG_TRACE("[Snake] Initializing Snake");

  this->size = static_cast<float>(this->settings.GetBoxSize());

  this->speed = this->size * 5.0f;
  this->length = this->settings.defaultSnakeLength;
  this->direction = {1.0f, 0.0f};
  this->grow = false;

  auto headTransform = Core::Math::Transform2D{{100.f, 100.0f}, 0, {this->size, this->size}};

  const auto snakeSegmentParams = SnakeSegmentParams{
      .index = 0,
      .transform = headTransform,
  };

  this->head = new SnakeSegment(snakeSegmentParams);

  this->body.push_back(this->head);

  for (int i = 1; i < this->length; i++) {
    Core::Math::Transform2D nextSegmentTransform = headTransform;
    nextSegmentTransform.position.x = headTransform.position.x - this->size * i;
    this->body.push_back(new SnakeSegment({
        .index = i,
        .transform = nextSegmentTransform,
    }));
  }

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
  Core::Math::Vector2D previousPosition = this->head->transform.position;
  Core::Math::Vector2D nextPosition = previousPosition;

  for (int i = 1; i < this->length; i++) {
    if (this->body[i] && this->body[i - 1]) {
      previousPosition = this->body[i]->transform.position;
      this->body[i]->Move(nextPosition);
      nextPosition = previousPosition;
    }
  }

  Core::Math::Vector2D newPosition = {
      this->head->transform.position.x + this->direction.x * this->size,
      this->head->transform.position.y + this->direction.y * this->size,
  };

  LOG_DEBUG("[Snake] Direction: {}", this->direction.ToString());
  LOG_DEBUG("[Snake] Head Position: {}", this->head->transform.position.ToString());
  LOG_DEBUG("[Snake] New Position: {}", newPosition.ToString());

  newPosition.x = std::roundf(newPosition.x / this->size) * this->size;
  newPosition.y = std::roundf(newPosition.y / this->size) * this->size;

  this->head->Move(newPosition);
}

void Snake::CheckIfShouldGrow()
{
  LOG_TRACE("[Snake] Checking if Snake should grow {}", this->grow);
  if (this->grow) {
    Core::Math::Transform2D newSegmentTransform = this->body.back()->transform;
    const auto segmentParams =
        SnakeSegmentParams{.index = this->length, .transform = newSegmentTransform};
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
    if (segment->transform.position.x > screenWidth) {
      segment->transform.position.x = 0;
    }
    else if (segment->transform.position.x < 0) {
      segment->transform.position.x = screenWidth;
    }
    else if (segment->transform.position.y > screenHeight) {
      segment->transform.position.y = 0;
    }
    else if (segment->transform.position.y < 0) {
      segment->transform.position.y = screenHeight;
    }
  }
}

Core::Math::Vector2D Snake::GetCenter() const
{
  const auto boxSize = static_cast<float>(this->settings.GetBoxSize());
  return {
      this->head->transform.position.x + boxSize / 2.0f,
      this->head->transform.position.y + boxSize / 2.0f,
  };
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
    // SIDE QUEST: [LOGGER] Support this style of logging
    // LOG_DEBUG("Deleting head at address: {}", this->head);
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
