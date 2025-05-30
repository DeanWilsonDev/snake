#pragma once
#include "../../renderer-2d/irenderer.h"

namespace Core {
class Color;
}

namespace Renderer2D {
class IRenderer;
}

namespace Raylib::Renderer {

struct RaylibRendererParams {
  // TODO: Not needed?
};

class RaylibRenderer : public Renderer2D::IRenderer {
 public:
  explicit RaylibRenderer(const RaylibRendererParams& params);
  ~RaylibRenderer() = default;

  void Render() override;
  void DrawRectangle(float x, float y, float width, float height, Core::Color) override;
  static Color RaylibRenderer::ConvertToRaylibColor(Core::Color color);
};
}  // namespace Raylib::Renderer
