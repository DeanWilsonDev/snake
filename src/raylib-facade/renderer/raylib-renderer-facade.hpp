#pragma once
#include "renderer-2d/irenderer.h"

namespace UserInterface {
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
  void Draw() override;
  void DrawRectangle(float x, float y, float width, float height, UserInterface::Color) override;
  static Color RaylibRendererFacade::ConvertToRaylibColor(UserInterface::Color color);
};
}  // namespace RaylibAdapter::Renderer
