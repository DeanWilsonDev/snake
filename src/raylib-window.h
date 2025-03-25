#pragma once

#include "iwindow.h"

class RaylibWindow : public IWindow {
 public:
  ~RaylibWindow() override;

  void createWindow(int width, int height, char* title) override;
  void closeWindow() override;
  void setTargetFPS(int targetFPS) override;
  bool shouldClose() override;
};
