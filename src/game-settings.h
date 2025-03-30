#pragma once

#include <iostream>
#define DEFAULT_SCREEN_WIDTH (500)
#define DEFAULT_SCREEN_HEIGHT (500)
#define DEFAULT_TARGET_FPS (60)
#define DEFAULT_BOX_SIZE (20.0f)
#define DEBUG_ENABLED false
#define WINDOW_TITLE "Snake"

struct GameSettings {
  int windowWidth = DEFAULT_SCREEN_WIDTH;
  int windowHeight = DEFAULT_SCREEN_HEIGHT;
  const char* windowTitle = WINDOW_TITLE;
  int targetFPS = DEFAULT_TARGET_FPS;
  // TODO: This could scale based on the resolution of the screen so that a full screen game isn't
  // way longer
  int boxSize = DEFAULT_BOX_SIZE;

  void Print()
  {
    std::cout << "------------ GAME SETTINGS -----------" << std::endl;
    std::cout << "Window Width: " << this->windowWidth << std::endl;
    std::cout << "Window Height: " << this->windowHeight << std::endl;
    std::cout << "Window Title: " << this->windowTitle << std::endl;
    std::cout << "Target FPS: " << this->targetFPS << std::endl;
    std::cout << "Box Size: " << this->boxSize << std::endl;
    std::cout << "--------------------------------------" << std::endl;
  }
};
