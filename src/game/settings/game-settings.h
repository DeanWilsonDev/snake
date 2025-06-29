#pragma once

#include "log.h"
#include "platform/window/screen.hpp"

#define DEFAULT_BOX_SIZE (20);
#define DEFAULT_MIN_BOX_SIZE (10);
#define DEFAULT_MAX_BOX_SIZE (40);
#define GRID_COLUMNS (25);
#define GRID_ROWS (25);
#define DEBUG_ENABLED false;
#define DEFAULT_SNAKE_LENGTH (5);

namespace Game {

struct GameSettings {
public:
  int minBoxSize = DEFAULT_MIN_BOX_SIZE;
  int maxBoxSize = DEFAULT_MAX_BOX_SIZE;
  int gridWidth = GRID_COLUMNS;
  int gridHeight = GRID_ROWS;
  bool isDebugEnabled = DEBUG_ENABLED;
  int defaultSnakeLength = DEFAULT_SNAKE_LENGTH;

  static int GetScreenWidth() { return Platform::Window::Screen::GetWidth(); }
  static int GetScreenHeight() { return Platform::Window::Screen::GetHeight(); }

  [[nodiscard]] int GetBoxSize() const
  {
    return std::clamp(
      std::min(
        this->GetScreenWidth() / this->gridWidth,
        this->GetScreenHeight() / this->gridHeight
        ),
      this->minBoxSize,
      this->maxBoxSize);
  }

  void Print()
  {
    LOG_INFO("------------ GAME SETTINGS -----------");
    LOG_INFO("Default Box Size: {}", this->boxSize);
    LOG_INFO("Current Box Size: {}", GetBoxSize());
    LOG_INFO("Grid Width: {}", this->gridWidth);
    LOG_INFO("Grid Height: {}", this->gridHeight);
    LOG_INFO("Screen Width: {}", this->GetScreenWidth());
    LOG_INFO("Screen Height: {}", this->GetScreenHeight());
    LOG_INFO("--------------------------------------");
  }
private:
  int boxSize = DEFAULT_BOX_SIZE;
};
}  // namespace Game
