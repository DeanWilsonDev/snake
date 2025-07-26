#pragma once

#include "platform/window/i-window.h"

namespace RaylibFacade::Window {

class RaylibWindowFacade final: public Platform::Window::IWindow {
 public:
  RaylibWindowFacade();
  ~RaylibWindowFacade() override;

  void CreateWindow(int width, int height, char* title) override;
  void CloseWindow() override;
  void SetTargetFPS(int targetFPS) override;
  bool ShouldClose() override;
  int GetScreenHeight() override;
  int GetScreenWidth() override;
  void SetWindowSize(int width, int height) override;
};
}  // namespace RaylibAdapter::Window
