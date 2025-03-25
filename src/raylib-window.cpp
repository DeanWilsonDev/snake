#include "raylib-window.h"
#include "raylib.h"

RaylibWindow::~RaylibWindow()
{
  closeWindow();
}

void RaylibWindow::createWindow(int width, int height, char* title)
{
  InitWindow(width, height, title);
}

void RaylibWindow::closeWindow()
{
  CloseWindow();
}

void RaylibWindow::setTargetFPS(int targetFPS)
{
  SetTargetFPS(targetFPS);
}

bool RaylibWindow::shouldClose()
{
  return WindowShouldClose();
}
