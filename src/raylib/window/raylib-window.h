#pragma once

namespace Platform {
class IWindow;
}

namespace Raylib::Window {

class RaylibWindow : public Platform::IWindow {
 public:
  RaylibWindow();
  ~RaylibWindow() override;

  static void CreateWindow(int width, int height, const char* title) override;
  static void CloseWindow() override;
  static void SetTargetFPS(int targetFPS) override;
  static bool ShouldClose() override;
};
}  // namespace Raylib::Window
