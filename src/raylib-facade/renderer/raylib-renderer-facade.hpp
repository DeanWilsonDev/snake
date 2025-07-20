#pragma once
#include "core/color.h"
#include "renderer-2d/irenderer.h"


namespace Renderer2D {
class IRenderer;
}

namespace RaylibFacade::Renderer {

class RaylibRendererFacade final : public Renderer2D::IRenderer {
 public:
  explicit RaylibRendererFacade();
  ~RaylibRendererFacade() override;

  void BeginDrawing() override;
  void EndDrawing() override;
  void ClearBackground(Core::Color color) override;

  void DrawRectangle(float x, float y, float width, float height, Core::Color) override;
  static Color ConvertToRaylibColor(Core::Color color);
};
}  // namespace RaylibAdapter::Renderer
