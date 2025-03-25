#include "snake.h"
#include "game-state.h"

Snake::Snake(GameState* state) : state(state)
{
  this->head = new SnakeBody(0, {100.0f, 100.0f});
  this->body.push_back(this->head);

  for (int i = 1; i < this->length; i++) {
    this->body.push_back(new SnakeBody(i, {100.0f - i * this->size, 100.0f}));
  }

  float size = this->settings.boxSize;
  float speed = DEFAULT_BOX_SIZE * 5.0f;
  int length = 3;
  Vector2 direction = {1.0f, 0.0f};
  SnakeBody* head;
  std::deque<SnakeBody*> body;
  bool grow = false;
}

// Move Player
void Snake::move()
{
  Vector2 newDirection;

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
    Vector2 newLogicalPosition = {
        this->head->position.x + this->direction.x * this->size,
        this->head->position.y + this->direction.y * this->size,
    };

    newLogicalPosition.x = std::roundf(newLogicalPosition.x / this->size) * this->size;
    newLogicalPosition.y = std::roundf(newLogicalPosition.y / this->size) * this->size;

    DEBUG_ENABLED&& std::cout << "this->Body Size: " << this->body.size() << std::endl;
    DEBUG_ENABLED&& std::cout << "this->length: " << this->length << std::endl;
    Vector2 previousPosition = this->head->position;
    Vector2 nextPosition = this->head->position;

    for (int i = 1; i < this->length; i++) {
      DEBUG_ENABLED&& std::cout << "Body[" << i << "]: " << this->body[i] << std::endl;
      DEBUG_ENABLED&& std::cout << "this->body[" << i << "].x: " << this->body[i]->position.x
                                << std::endl;
      DEBUG_ENABLED&& std::cout << "this->body[" << i << "].y: " << this->body[i]->position.y
                                << std::endl;

      if (this->body[i] && this->body[i - 1]) {
        previousPosition = this->body[i]->position;
        this->body[i]->position.x = nextPosition.x;
        this->body[i]->position.y = nextPosition.y;
        nextPosition = previousPosition;
      }

      DEBUG_ENABLED&& std::cout << "this->body[" << i - 1
                                << "].x: " << this->body[i - 1]->position.x << std::endl;
      DEBUG_ENABLED&& std::cout << "this->body[" << i - 1
                                << "].y: " << this->body[i - 1]->position.y << std::endl;
    }

    this->head->position.x = newLogicalPosition.x;
    this->head->position.y = newLogicalPosition.y;
    if (this->grow) {
      this->body.push_back(new SnakeBody(this->length, this->body.back()->position));
      this->length++;
      this->grow = false;
    }

    accumulatedDistance -= this->size;

    if (directionChanged) {
      directionChanged = false;
    }

    // Move this->to opposite side
    {
      for (int i = 0; i < this->body.size(); i++) {
        if (this->body[i]->position.x > SCREEN_WIDTH) {
          this->body[i]->position.x = 0;
        }
        else if (this->body[i]->position.x < 0) {
          this->body[i]->position.x = SCREEN_WIDTH;
        }
        else if (this->body[i]->position.y > SCREEN_HEIGHT) {
          this->body[i]->position.y = 0;
        }
        else if (this->body[i]->position.y < 0) {
          this->body[i]->position.y = SCREEN_HEIGHT;
        }
      }
    };
  }

  if (this->head) {
    DEBUG_ENABLED&& std::cout << "HEAD: " << this->head << std::endl;
  }

  for (int i = 0; i < this->body.size(); i++) {
    DEBUG_ENABLED&& std::cout << "Body[" << i << "]: " << this->body[i] << std::endl;
    if (this->head != nullptr && this->body[i] != this->head) {
      if (DEBUG_ENABLED) {
        DrawRectangleRec(this->body[i]->getBounds(), RED);
      }

      if (CheckCollisionRecs(this->head->getBounds(), this->body[i]->getBounds())) {
        this->state->setState(STATE_GAME_OVER);
      }
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
      DEBUG_ENABLED&& std::cout << "Deleting body segment at address: " << segment << std::endl;
      delete segment;
      DEBUG_ENABLED&& std::cout << "Body segment at address: " << segment
                                << " successfully destroyed" << std::endl;
    }
    else {
      DEBUG_ENABLED&& std::cout << "Found null segment in body!" << std::endl;
    }
  }

  this->body.clear();

  if (head) {
    DEBUG_ENABLED&& std::cout << "Deleting head at address: " << this->head << std::endl;
    delete this->head;
    DEBUG_ENABLED&& std::cout << "Setting head to nullptr" << std::endl;
    this->head = nullptr;
    DEBUG_ENABLED&& std::cout << "Head successfully destroyed" << std::endl;
  }
  else {
    DEBUG_ENABLED&& std::cout << "Found null segment in head!" << std::endl;
  }
}
