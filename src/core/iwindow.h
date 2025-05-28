#pragma once
class IWindow {
 public:
  virtual ~IWindow() = default;
  virtual void createWindow(int width, int height, char* title) = 0;
  virtual void closeWindow() = 0;
  virtual void setTargetFPS(int targetFPS) = 0;
  virtual bool shouldClose() = 0;
};
