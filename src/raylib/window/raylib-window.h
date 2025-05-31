#pragma once

#include "../../platform/window/iwindow.h"

namespace RaylibAdapter::Window {

class RaylibWindow : public Platform::Window::IWindow {
 public:
  RaylibWindow();
  ~RaylibWindow() override;

  void CreateWindow(int width, int height, char* title) override;
  void CloseWindow() override;
  void SetTargetFPS(int targetFPS) override;
  bool ShouldClose() override;
};
}  // namespace RaylibAdapter::Window
