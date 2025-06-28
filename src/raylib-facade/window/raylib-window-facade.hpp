#pragma once

#include "../../platform/window/iwindow.h"

namespace RaylibFacade::Window {

class RaylibWindowFacade : public Platform::Window::IWindow {
 public:
  RaylibWindowFacade();
  ~RaylibWindowFacade() override;

  void CreateWindow(int width, int height, char* title) override;
  void CloseWindow() override;
  void SetTargetFPS(int targetFPS) override;
  bool ShouldClose() override;
  int GetScreenHeight() override;
  int GetScreenWidth() override;
};
}  // namespace RaylibAdapter::Window
