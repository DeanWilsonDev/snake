//
// Created by Dean Wilson on 30/5/2025.
//

#ifndef WINDOW_CONFIG_H
#define WINDOW_CONFIG_H
#include <string>

namespace Platform::Config::Window {

#define DEFAULT_SCREEN_WIDTH (1280)
#define DEFAULT_SCREEN_HEIGHT (720)
#define DEFAULT_TARGET_FPS (60)

struct WindowConfig {
  int width = DEFAULT_SCREEN_WIDTH;
  int height = DEFAULT_SCREEN_HEIGHT;
  int targetFPS = DEFAULT_TARGET_FPS;
  bool fullscreen = false;
  std::string title = "My Game";
  bool vsync = true;
};

#endif  // WINDOW_CONFIG_H
}
