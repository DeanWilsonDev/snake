#include "raylib-window-adapter.hpp"
#include "log.h"
#include "raylib.h"

namespace RaylibAdapter::Window {

RaylibWindowAdapter::RaylibWindowAdapter()
{
  LOG_TRACE("Initializing Window");
}

RaylibWindowAdapter::~RaylibWindowAdapter()
{
  CloseWindow();
}

void RaylibWindowAdapter::CreateWindow(int width, int height, char* title)
{
  LOG_TRACE("Creating Window");
  ::InitWindow(width, height, title);
}

void RaylibWindowAdapter::CloseWindow()
{
  ::CloseWindow();
}

void RaylibWindowAdapter::SetTargetFPS(const int targetFPS)
{
  ::SetTargetFPS(targetFPS);
}

bool RaylibWindowAdapter::ShouldClose()
{
  return WindowShouldClose();
}

int RaylibWindowAdapter::GetScreenHeight()
{
  return ::GetScreenHeight();
}

int RaylibWindowAdapter::GetScreenWidth()
{
  return ::GetScreenHeight();
}

}  // namespace RaylibAdapter::Window
