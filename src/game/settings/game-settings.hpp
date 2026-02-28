#pragma once

#include <umbra/log.h>
#include <algorithm>

#define DEFAULT_BOX_SIZE (20)
#define DEFAULT_MIN_BOX_SIZE (10)
#define DEFAULT_MAX_BOX_SIZE (40)
#define DEFAULT_SCREEN_WIDTH (1280)
#define DEFAULT_SCREEN_HEIGHT (720)
#define GRID_COLUMNS (25)
#define GRID_ROWS (25)
#define DEBUG_ENABLED (true)
#define DEFAULT_SNAKE_LENGTH (5)

namespace Game {

/**
 * @brief Manages configurable settings for the game, including grid dimensions, box size limits,
 *        debug mode status, and default snake length.
 */
struct GameSettings {
 public:
  int minBoxSize = DEFAULT_MIN_BOX_SIZE;
  int maxBoxSize = DEFAULT_MAX_BOX_SIZE;
  int gridWidth = GRID_COLUMNS;
  int gridHeight = GRID_ROWS;
  bool isDebugEnabled = DEBUG_ENABLED;
  int defaultSnakeLength = DEFAULT_SNAKE_LENGTH;
  int screenWidth = DEFAULT_SCREEN_WIDTH;
  int screenHeight = DEFAULT_SCREEN_HEIGHT;

  [[nodiscard]] int GetScreenWidth() const { return this->screenWidth; }
  [[nodiscard]] int GetScreenHeight() const { return this->screenHeight; }
  void SetScreenResolution(const int width, const int height)
  {
    this->screenWidth = width;
    this->screenHeight = height;
  }

  [[nodiscard]] int GetBoxSize() const
  {
    return std::clamp(
        std::min(screenWidth / this->gridWidth, screenHeight / this->gridHeight),
        this->minBoxSize,
        this->maxBoxSize
    );
  }

  void Print() const
  {
    LOG_INFO("------------ GAME SETTINGS -----------");
    LOG_INFO("Default Min Box Size: {}", this->minBoxSize);
    LOG_INFO("Default Max Box Size: {}", this->maxBoxSize);
    LOG_INFO("Default Box Size: {}", this->boxSize);
    LOG_INFO("Current Box Size: {}", GetBoxSize());
    LOG_INFO("Grid Width: {}", this->gridWidth);
    LOG_INFO("Grid Height: {}", this->gridHeight);
    LOG_INFO("Debug Mode: {}", this->isDebugEnabled);
    LOG_INFO("Default Snake Length: {}", this->defaultSnakeLength);
    LOG_INFO("Screen Width: {}", this->screenWidth);
    LOG_INFO("Screen Height: {}", this->screenHeight);
    LOG_INFO("--------------------------------------");
  }

 private:
  int boxSize = DEFAULT_BOX_SIZE;
};
}  // namespace Game
