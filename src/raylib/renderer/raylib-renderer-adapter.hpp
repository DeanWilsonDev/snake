#pragma once
#include "../../renderer-2d/irenderer.h"

namespace Core {
class Color;
}

namespace Renderer2D {
class IRenderer;
}

namespace RaylibAdapter::Renderer {

class RaylibRendererAdapter : public Renderer2D::IRenderer {
 public:
  explicit RaylibRendererAdapter();
  ~RaylibRendererAdapter() override;

  void Render() override;
  void DrawRectangle(float x, float y, float width, float height, Core::Color) override;
  static Color RaylibRendererAdapter::ConvertToRaylibColor(Core::Color color);
};
}  // namespace RaylibAdapter::Renderer
