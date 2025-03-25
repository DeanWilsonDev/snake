#include "apple.h"
#include "snake.h"
#include "game-state.h"

Apple::Apple(const AppleParams& params)
    : state(params.state)
    , settings(params.settings)
    , snake(params.snake)
    , size(params.settings.boxSize / 2.0f)
{
  this->position = this->getNewPosition();
}

void Apple::update()
{
  // TODO: Move this to the renderer
  DrawRectangleRec(
      {
          this->position.x,
          this->position.y,
          this->size,
          this->size,
      },
      RED
  );

  // TODO: Create functions for these
  Vector2 snakeHeadCenter = {
      this->snake->head->position.x + this->settings.boxSize / 2.0f,
      this->snake->head->position.y + this->settings.boxSize / 2.0f,
  };

  Vector2 appleCenter = {
      this->position.x + (this->settings.boxSize - this->settings.boxSize / 2.0f) / 2.0f,
      this->position.y + (this->settings.boxSize - this->settings.boxSize / 2.0f) / 2.0f,
  };

  if (CheckCollisionCircles(
          snakeHeadCenter, this->snake->size / 2.0f - 2.0f, appleCenter, this->size - 2.0f
      )) {
    this->position = this->getNewPosition();

    this->state->increaseScore();
    // TODO make set function
    this->snake->grow = true;
  }
};

void Apple::getNewPosition()
{
  return {
      GetRandomValue(0, (this->settings.windowWidth / this->settings.boxSize) - 1) *
              this->settings.boxSize +
          (this->settings.boxSize - this->settings.boxSize / 2.0f) / 2.0f,
      GetRandomValue(0, (this->settings.windowHeight / this->settings.boxSize) - 1) *
              this->settings.boxSize +
          (this->settings.boxSize - this->settings.boxSize / 2.0f) / 2.0f
  };
}
