#include "raylib-renderer-facade.hpp"
#include "log.h"
#include "raylib.h"
#include "core/color.h"

namespace RaylibFacade::Renderer {

RaylibRendererFacade::RaylibRendererFacade()
{
  LOG_TRACE("Initializing Raylib Renderer");
}
RaylibRendererFacade::~RaylibRendererFacade() = default;

void RaylibRendererFacade::BeginDrawing()
{
  return ::BeginDrawing();
}
void RaylibRendererFacade::EndDrawing()
{
  return ::EndDrawing();
}

void RaylibRendererFacade::ClearBackground(const Core::Color color)
{
  return ::ClearBackground(ConvertToRaylibColor(color));
}

Color RaylibRendererFacade::ConvertToRaylibColor(const Core::Color color)
{
  return Color(color.red, color.green, color.blue, color.alpha);
}

void RaylibRendererFacade::DrawRectangle(
    float x, float y, float width, float height, Core::Color color
)
{
  DrawRectangleRec({x, y, width, height}, ConvertToRaylibColor(color));
}
}  // namespace RaylibFacade::Renderer
