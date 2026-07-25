#pragma once

#include "core/window/i-window.hpp"

namespace RaylibFacade::Window {

class RaylibWindowFacade final : public Core::Window::IWindow {
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

 private:
  bool closed = false;
};
}  // namespace RaylibFacade::Window
