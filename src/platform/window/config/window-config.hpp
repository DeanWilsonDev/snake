//
// Created by Dean Wilson on 30/5/2025.
//

#ifndef WINDOW_CONFIG_H
#define WINDOW_CONFIG_H
#include <string>

namespace Platform::Config::Window {

struct WindowConfig {
  int width = 1280;
  int height = 720;
  bool fullscreen = false;
  std::string title = "My Game";
  bool vsync = true;
};

#endif  // WINDOW_CONFIG_H
}
