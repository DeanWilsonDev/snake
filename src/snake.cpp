#include "snake.h"
#include "game-settings.h"
#include "log.h"
#include "game-session.h"
#include "snake-body.h"
#include "raylib.h"
#include <cstddef>

Snake::Snake(const SnakeParams& snakeParams)
    : session(snakeParams.session), settings(snakeParams.settings)
{
  LOG_TRACE("Initializing Snake");
  this->size = this->settings.boxSize;
  this->speed = this->settings.boxSize * 5.0f;
  this->length = this->settings.defaultSnakeLength;
  this->direction = {1.0f, 0.0f};
  this->grow = false;

  this->head = new SnakeBody(0, {100.f, 100.0f}, this->size);
  this->body.push_back(this->head);

  for (int i = 1; i < this->length; i++) {
    this->body.push_back(new SnakeBody(i, {100.0f - (i * this->size), 100.0f}, this->size));
  }

  LOG_TRACE("Finished Initializing Snake");
}

void Snake::update()
{
  LOG_TRACE("Snake Update Begin");
  Vector2 newDirection = this->direction;

  if (this->direction.y != 0 && !directionChanged) {
    if (IsKeyPressed(KEY_A)) {
      newDirection = {-1.0f, 0.0f};
    }
    if (IsKeyPressed(KEY_D)) {
      newDirection = {1.0f, 0.0f};
    }
  }
  if (this->direction.x != 0 && !directionChanged) {
    if (IsKeyPressed(KEY_S)) {
      newDirection = {0.0f, 1.0f};
    }
    if (IsKeyPressed(KEY_W)) {
      newDirection = {0.0f, -1.0f};
    }
  }

  if (newDirection.x != this->direction.x && newDirection.y != this->direction.y) {
    directionChanged = true;
    this->direction = newDirection;
  }
  accumulatedDistance += this->speed * GetFrameTime();

  if (accumulatedDistance >= this->size) {
    this->move();
    this->checkIfShouldGrow();

    accumulatedDistance -= this->size;

    if (directionChanged) {
      directionChanged = false;
    }

    this->teleport();
  }

  if (this->head) {
    LOG_DEBUG("HEAD {}", this->head->index);
  }

  for (int i = 0; i < this->body.size(); i++) {
    DEBUG_ENABLED&& std::cout << "Body[" << i << "]: " << this->body[i] << std::endl;
    DEBUG_ENABLED&& std::cout << "Body[" << i << "]: " << this->body[i] << std::endl;
    if (this->head != nullptr && this->body[i] != this->head) {
      if (DEBUG_ENABLED) {
        DrawRectangleRec(this->body[i]->getBounds(), RED);
      }

      if (CheckCollisionRecs(this->head->getBounds(), this->body[i]->getBounds())) {
        LOG_INFO("Head hit body part with index: {}", i);
        this->session->setState(STATE_GAME_OVER);
      }
    }
  }
}

void Snake::move()
{
  Vector2 previousPosition = this->head->position;
  Vector2 nextPosition = this->head->position;

  for (int i = 1; i < this->length; i++) {
    if (this->body[i] && this->body[i - 1]) {
      previousPosition = this->body[i]->position;
      this->body[i]->move(nextPosition);
      nextPosition = previousPosition;
    }
  }

  Vector2 newPosition = {
      this->head->position.x + this->direction.x * this->size,
      this->head->position.y + this->direction.y * this->size,
  };
  LOG_DEBUG("Direction ({}, {})", this->direction.x, this->direction.y);
  LOG_DEBUG("Head Position ({}, {})", this->head->position.x, this->head->position.y);
  LOG_DEBUG("New Position ({}, {})", newPosition.x, newPosition.y);

  newPosition.x = std::roundf(newPosition.x / this->size) * this->size;
  newPosition.y = std::roundf(newPosition.y / this->size) * this->size;

  this->head->move(newPosition);
}

void Snake::checkIfShouldGrow()
{
  if (this->grow) {
    this->body.push_back(new SnakeBody(this->length, this->body.back()->position, this->size));
    this->length++;
    this->grow = false;
  }
}

void Snake::teleport()
{
  for (int i = 0; i < this->body.size(); i++) {
    if (this->body[i]->position.x > this->settings.windowWidth) {
      this->body[i]->position.x = 0;
    }
    else if (this->body[i]->position.x < 0) {
      this->body[i]->position.x = this->settings.windowWidth;
    }
    else if (this->body[i]->position.y > this->settings.windowHeight) {
      this->body[i]->position.y = 0;
    }
    else if (this->body[i]->position.y < 0) {
      this->body[i]->position.y = this->settings.windowHeight;
    }
  }
}

void Snake::destroy()
{
  if (!body.empty() && body.front() == head) {
    body.pop_front();
  }

  for (auto segment : body) {
    if (segment) {
      int index = segment->index;
      LOG_DEBUG("Deleting segment with index: {}", index);
      delete segment;
      LOG_DEBUG("Successfully deleted segment with index: {}", index);
    }
    else {
      LOG_DEBUG("Found null segment in body!");
    }
  }

  this->body.clear();

  if (head) {
    DEBUG_ENABLED&& std::cout << "Deleting head at address: " << this->head << std::endl;
    delete this->head;
    LOG_DEBUG("Setting head to nullptr");
    this->head = nullptr;
    LOG_DEBUG("Head successfully destroyed");
  }
  else {
    LOG_DEBUG("Found null segment in head!");
  }
}
