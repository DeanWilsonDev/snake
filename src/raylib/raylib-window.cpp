#include "raylib-window.h"
#include "log.h"
#include "raylib.h"

RaylibWindow::RaylibWindow()
{
  LOG_TRACE("Initializing Window");
}

RaylibWindow::~RaylibWindow()
{
  closeWindow();
}

void RaylibWindow::createWindow(int width, int height, char* title)
{
  LOG_TRACE("Creating Window");
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
