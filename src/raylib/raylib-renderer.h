#pragma once
#include "../game-settings.h"
#include "../game-session.h"
#include "../render-2d/irenderer.h"

class Color;

struct RaylibRendererParams {
  GameSettings settings;
};

class RaylibRenderer : public IRenderer {
 public:
  explicit RaylibRenderer(const RaylibRendererParams& params);
  ~RaylibRenderer() = default;

  void Render() override;
  void DrawRectangle(float x, float y, float width, float height, Core::Color) override;
  static Color RaylibRenderer::ConvertToRaylibColor(Core::Color color);

 private:
  GameSettings settings;
};
