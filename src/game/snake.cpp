#include "snake.hpp"
#include "Settings/game-settings.h"
#include "log.h"
#include "../game-session.h"
#include "snake-segment.hpp"
#include "../platform/input/input.hpp"

// Main Quest: clean this up to the point that raylib doesn't need to be imported

namespace Game {

Snake::~Snake() = default;

Snake::Snake(const SnakeParams& snakeParams)
    : renderComponent(snakeParams.renderComponent), colliderComponent(snakeParams.colliderComponent), settings(snakeParams.settings)
{
}

Snake* Snake::Initialize()
{
  LOG_TRACE("Initializing Snake");

  this->size = this->settings.GetBoxSize();

  this->speed = this->size * 5.0f;
  this->length = this->settings.defaultSnakeLength;
  this->direction = {1.0f, 0.0f};
  this->grow = false;

  const Core::Math::Transform2D headTransform = {{100.f, 100.0f}, 0, {this->size, this->size}};
  this->head = new SnakeSegment(0, headTransform);

  this->body.push_back(this->head);

  for (int i = 1; i < this->length; i++) {
    Core::Math::Transform2D nextSegmentTransform = headTransform;
    nextSegmentTransform.position.x = headTransform.position.x - (i * this->size);
    this->body.push_back(new SnakeSegment(i, nextSegmentTransform));
  }

  LOG_TRACE("Finished Initializing Snake");
  return this;
}

void Snake::Update(float deltaTime)
{
  LOG_TRACE("Snake Update Begin");
  Core::Math::Vector2D newDirection = this->direction;

  if (this->direction.y != 0 && !directionChanged) {
    if (Platform::Input::Input::IsKeyPressed(Platform::Input::KEY_A)) {
      newDirection = {-1.0f, 0.0f};
    }
    if (Platform::Input::Input::IsKeyPressed(Platform::Input::KEY_D)) {
      newDirection = {1.0f, 0.0f};
    }
  }
  if (this->direction.x != 0 && !directionChanged) {
    if (Platform::Input::Input::IsKeyPressed(Platform::Input::KEY_S)) {
      newDirection = {0.0f, 1.0f};
    }
    if (Platform::Input::Input::IsKeyPressed(Platform::Input::KEY_W)) {
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

  if (this->head) {
    LOG_DEBUG("HEAD {}", this->head->index);
  }

  for (int i = 0; i < this->body.size(); i++) {
    this->debugEnabled&& std::cout << "Body[" << i << "]: " << this->body[i] << std::endl;
    this->debugEnabled&& std::cout << "Body[" << i << "]: " << this->body[i] << std::endl;

    if (this->head != nullptr && this->body[i] != this->head) {
      // Side Quest: Allow for Debug drawing in some fashion

      if (this->debugEnabled) {
        DrawRectangleRec(this->body[i]->GetBounds(), RED);
      }

      if (CheckCollisionRecs(this->head->GetBounds(), this->body[i]->GetBounds())) {
        LOG_INFO("Head hit body part with index: {}", i);
        // TODO: come up with a clean way for the GameplayStateMachine to change the state on death
        // And event would probably be ideal for this.
        this->session->setState(STATE_GAME_OVER);
      }
    }
  }
}

void Snake::Move()
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

  LOG_DEBUG("Direction ({}, {})", this->direction.x, this->direction.y);
  LOG_DEBUG(
      "Head Position ({}, {})", this->head->transform.position.x, this->head->transform.position.y
  );
  LOG_DEBUG("New Position ({}, {})", newPosition.x, newPosition.y);

  newPosition.x = std::roundf(newPosition.x / this->size) * this->size;
  newPosition.y = std::roundf(newPosition.y / this->size) * this->size;

  this->head->Move(newPosition);
}

void Snake::CheckIfShouldGrow()
{
  LOG_TRACE("[Snake] Checking if Snake should grow {}", this->grow);
  if (this->grow) {
    this->body.push_back(new SnakeSegment(this->length, this->body.back()->transform));
    this->length++;
    this->grow = false;

    LOG_TRACE("[Snake] Snake Grew Successfully");
  }
}

void Snake::Teleport() const
{
  for (int i = 0; i < this->body.size(); i++) {
    if (this->body[i]->transform.position.x > this->settings.GetScreenWidth()) {
      this->body[i]->transform.position.x = 0;
    }
    else if (this->body[i]->transform.position.x < 0) {
      this->body[i]->transform.position.x = this->settings.GetScreenWidth();
    }
    else if (this->body[i]->transform.position.y > this->settings.GetScreenHeight()) {
      this->body[i]->transform.position.y = 0;
    }
    else if (this->body[i]->transform.position.y < 0) {
      this->body[i]->transform.position.y = this->settings.GetScreenHeight();
    }
  }
}

Core::Math::Vector2D Snake::GetCenter() const
{
  const int boxSize = this->settings.GetBoxSize();
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
    this->debugEnabled&& std::cout << "Deleting head at address: " << this->head << std::endl;
    delete this->head;
    LOG_DEBUG("Setting head to nullptr");
    this->head = nullptr;
    LOG_DEBUG("Head successfully destroyed");
  }
  else {
    LOG_DEBUG("Found null segment in head!");
  }
}
}  // namespace Game
