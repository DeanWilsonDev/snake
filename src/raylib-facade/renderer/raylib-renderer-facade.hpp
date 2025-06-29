#pragma once
#include "renderer-2d/irenderer.h"

namespace Core {
class Color;
}

namespace Renderer2D {
class IRenderer;
}

namespace RaylibFacade::Renderer {

class RaylibRendererFacade : public Renderer2D::IRenderer {
 public:
  explicit RaylibRendererFacade();
  ~RaylibRendererFacade() override;

  void Render() override;
  void DrawRectangle(float x, float y, float width, float height, Core::Color) override;
  static Color RaylibRendererFacade::ConvertToRaylibColor(Core::Color color);
};
}  // namespace RaylibAdapter::Renderer
