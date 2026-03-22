#pragma once

#include "engine/config/game-settings.hpp"

#include <umbra/log.h>
#include <algorithm>

inline constexpr int DefaultBoxSize = 20;
inline constexpr int DefaultMinBoxSize = 10;
inline constexpr int DefaultMaxBoxSize = 40;
inline constexpr int GridColumns = 25;
inline constexpr int GridRows = 25;
inline constexpr int DefaultSnakeLength = 5;

namespace Game {

/**
 * @brief Manages configurable settings for the game, including grid dimensions, box size limits,
 *        debug mode status, and default snake length.
 */
struct SnakeGameSettings : public Engine::Config::GameSettings {
 public:
  int minBoxSize = DefaultMinBoxSize;
  int maxBoxSize = DefaultMaxBoxSize;
  int gridWidth = GridColumns;
  int gridHeight = GridRows;
  int defaultSnakeLength = DefaultSnakeLength;

  [[nodiscard]] int GetBoxSize(int screenWidth, int screenHeight) const
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
    LOG_INFO("Grid Width: {}", this->gridWidth);
    LOG_INFO("Grid Height: {}", this->gridHeight);
    LOG_INFO("Debug Mode: {}", this->debug.enabled);
    LOG_INFO("Debug Logs Enabled: {}", this->debug.showDebugLogs);
    LOG_INFO("Default Snake Length: {}", this->defaultSnakeLength);
    LOG_INFO("--------------------------------------");
  }

 private:
  int boxSize = DefaultBoxSize;
};
}  // namespace Game
