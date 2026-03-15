//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once
namespace Engine::Config {

inline constexpr int DefaultScreenWidth = 1280;
inline constexpr int DefaultScreenHeight = 720;
inline constexpr int DefaultTargetFPS = 60;

struct WindowConfig {
  int width = DefaultScreenWidth;
  int height = DefaultScreenHeight;
  int targetFPS = DefaultTargetFPS;
  bool fullscreen = false;
  bool vsync = true;

  [[nodiscard]] int GetScreenWidth() const { return this->width; }
  [[nodiscard]] int GetScreenHeight() const { return this->height; }
  void SetScreenResolution(const int width, const int height)
  {
    this->width = width;
    this->height = height;
  }
};

}  // namespace Engine::Config
