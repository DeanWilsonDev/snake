#pragma once
#include "core/color.hpp"
#include "core/i-renderer.hpp"

struct Color;  // Raylib Color

namespace Core {
class IRenderer;
}

namespace RaylibFacade::Renderer {

class RaylibRendererFacade final : public Core::IRenderer {
 public:
  explicit RaylibRendererFacade();
  ~RaylibRendererFacade() override;

  void BeginDrawing() override;
  void EndDrawing() override;
  void ClearBackground(Core::Color color) override;

  void DrawRectangle(float x, float y, float width, float height, Core::Color) override;
  static Color ConvertToRaylibColor(Core::Color color);
};
}  // namespace RaylibFacade::Renderer
