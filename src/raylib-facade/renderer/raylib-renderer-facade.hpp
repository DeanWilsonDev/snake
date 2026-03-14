#pragma once
#include "core/color/color-rgba.hpp"
#include "core/rendering/i-renderer.hpp"

struct Color;  // Raylib Color

namespace Core {

namespace Rendering {
class IRenderer;
}
}  // namespace Core

namespace RaylibFacade::Renderer {

class RaylibRendererFacade final : public Core::Rendering::IRenderer {
 public:
  explicit RaylibRendererFacade();
  ~RaylibRendererFacade() override;

  void BeginDrawing() override;
  void EndDrawing() override;
  void ClearBackground(Core::Color::ColorRGBA color) override;

  void DrawRectangle(float x, float y, float width, float height, Core::Color::ColorRGBA) const override;
  static Color ConvertToRaylibColor(Core::Color::ColorRGBA color);
};
}  // namespace RaylibFacade::Renderer
