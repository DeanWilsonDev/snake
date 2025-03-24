#include "apple.h"
#include "game-state.h"

Apple::Apple(GameState* state, Snake* snake) : state(state)
{
  this->position = {
      GetRandomValue(0, (SCREEN_WIDTH / DEFAULT_BOX_SIZE) - 1) * DEFAULT_BOX_SIZE +
          (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
      GetRandomValue(0, (SCREEN_HEIGHT / DEFAULT_BOX_SIZE) - 1) * DEFAULT_BOX_SIZE +
          (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f
  };

  this->size = DEFAULT_BOX_SIZE / 2.0f;
  this->snake = snake;
};

void Apple::update()
{
  DrawRectangleRec(
      {
          this->position.x,
          this->position.y,
          this->size,
          this->size,
      },
      RED
  );

  float appleOffset = DEFAULT_BOX_SIZE + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f;

  Vector2 snakeHeadCenter = {
      this->snake->head->position.x + DEFAULT_BOX_SIZE / 2,
      this->snake->head->position.y + DEFAULT_BOX_SIZE / 2,
  };

  Vector2 appleCenter = {
      this->position.x + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
      this->position.y + (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
  };

  if (CheckCollisionCircles(
          snakeHeadCenter, this->snake->size / 2 - 2, appleCenter, this->size - 2
      )) {
    this->position = {
        GetRandomValue(0, (SCREEN_WIDTH / DEFAULT_BOX_SIZE) - 1) * DEFAULT_BOX_SIZE +
            (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f,
        GetRandomValue(0, (SCREEN_HEIGHT / DEFAULT_BOX_SIZE) - 1) * DEFAULT_BOX_SIZE +
            (DEFAULT_BOX_SIZE - DEFAULT_BOX_SIZE / 2) / 2.0f
    };

    state->increaseScore();
    // TODO make set function
    this->snake->grow = true;
  }
};
