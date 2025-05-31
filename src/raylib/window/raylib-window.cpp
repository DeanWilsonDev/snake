#include "raylib-window.h"
#include "log.h"
#include "raylib.h"

namespace RaylibAdapter::Window {

RaylibWindow::RaylibWindow()
{
  LOG_TRACE("Initializing Window");
}

RaylibWindow::~RaylibWindow()
{
  CloseWindow();
}

void RaylibWindow::CreateWindow(int width, int height, char* title)
{
  LOG_TRACE("Creating Window");
  ::InitWindow(width, height, title);
}

void RaylibWindow::CloseWindow()
{
  ::CloseWindow();
}

void RaylibWindow::SetTargetFPS(const int targetFPS)
{
  ::SetTargetFPS(targetFPS);
}

bool RaylibWindow::ShouldClose()
{
  return WindowShouldClose();
}
}  // namespace RaylibAdapter::Window
