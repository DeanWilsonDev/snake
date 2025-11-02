#include "raylib-window-facade.hpp"
#include <umbra/log.h>
#include "raylib.h"

namespace RaylibFacade::Window {

RaylibWindowFacade::RaylibWindowFacade()
{
  LOG_CORE_TRACE("Initializing Window");
}

RaylibWindowFacade::~RaylibWindowFacade()
{
  CloseWindow();
}

void RaylibWindowFacade::CreateWindow(int width, int height, char* title)
{
  LOG_CORE_TRACE("Creating Window");
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

}  // namespace RaylibFacade::Window
