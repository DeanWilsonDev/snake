#pragma once

#include "../../platform/window/iwindow.h"

namespace RaylibAdapter::Window {

class RaylibWindowAdapter : public Platform::Window::IWindow {
 public:
  RaylibWindowAdapter();
  ~RaylibWindowAdapter() override;

  void CreateWindow(int width, int height, char* title) override;
  void CloseWindow() override;
  void SetTargetFPS(int targetFPS) override;
  bool ShouldClose() override;
  int GetScreenHeight() override;
  int GetScreenWidth() override;
};
}  // namespace RaylibAdapter::Window
