#pragma once

#include "log.h"
#define DEFAULT_SCREEN_WIDTH (500)
#define DEFAULT_SCREEN_HEIGHT (500)
#define DEFAULT_TARGET_FPS (60)
#define DEFAULT_BOX_SIZE (20.0f)
#define DEBUG_ENABLED true
#define WINDOW_TITLE "Snake"

namespace Game {

struct GameSettings {
  int windowWidth = DEFAULT_SCREEN_WIDTH;
  int windowHeight = DEFAULT_SCREEN_HEIGHT;
  const char* windowTitle = WINDOW_TITLE;
  int targetFPS = DEFAULT_TARGET_FPS;
  // TODO: This could scale based on the resolution of the screen so that a full screen game isn't
  // way longer
  int boxSize = DEFAULT_BOX_SIZE;
  int defaultSnakeLength = 5;

  void Print()
  {
    LOG_INFO("------------ GAME SETTINGS -----------");
    LOG_INFO("Window Width: {}", this->windowWidth);
    LOG_INFO("Window Height: {}", this->windowHeight);
    LOG_INFO("Window Title: {}", this->windowTitle);
    LOG_INFO("Target FPS: {}", this->targetFPS);
    LOG_INFO("Box Size: {}", this->boxSize);
    LOG_INFO("--------------------------------------");
  }
};
}  // namespace Game
