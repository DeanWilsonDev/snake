#include "raylib-window-facade.hpp"
#include "log.h"
#include "raylib.h"

namespace RaylibFacade::Window {

RaylibWindowFacade::RaylibWindowFacade()
{
  LOG_TRACE("Initializing Window");
}

RaylibWindowFacade::~RaylibWindowFacade()
{
  CloseWindow();
}

void RaylibWindowFacade::CreateWindow(int width, int height, char* title)
{
  LOG_TRACE("Creating Window");
  ::InitWindow(width, height, title);
}

void RaylibWindowFacade::CloseWindow()
{
  ::CloseWindow();
}

void RaylibWindowFacade::SetTargetFPS(const int targetFPS)
{
  ::SetTargetFPS(targetFPS);
}

bool RaylibWindowFacade::ShouldClose()
{
  return WindowShouldClose();
}

int RaylibWindowFacade::GetScreenHeight()
{
  return ::GetScreenHeight();
}

int RaylibWindowFacade::GetScreenWidth()
{
  return ::GetScreenHeight();
}

void RaylibWindowFacade::SetWindowSize(const int width, const int height)
{
  ::SetWindowSize(width, height);
}

}  // namespace RaylibAdapter::Window
