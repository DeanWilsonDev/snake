#pragma once

namespace Platform::Window {

class IWindow {
 public:
  // 1UP: [IWindow] Allow for passing in the window config settings for defaults
  virtual ~IWindow() = default;
  virtual void CreateWindow(int width, int height, char* title) = 0;
  virtual void CloseWindow() = 0;
  virtual void SetTargetFPS(int targetFPS) = 0;
  virtual bool ShouldClose() = 0;
  virtual void SetWindowSize(int width, int height) = 0;
  virtual int GetScreenHeight() = 0;
  virtual int GetScreenWidth() = 0;
};
}  // namespace Platform
