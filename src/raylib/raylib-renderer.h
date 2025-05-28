#pragma once
#include "../game-settings.h"
#include "../game-session.h"
#include "../core/irenderer.h"

class Color;

struct RaylibRendererParams {
  GameSettings settings;
  GameSession* session;
};

class RaylibRenderer : public IRenderer {
 public:
  RaylibRenderer(const RaylibRendererParams& params);
  ~RaylibRenderer() = default;

  void Render() override;
  void DrawRectangle(float x, float y, float width, float height, Core::Color) override;
  static Color RaylibRenderer::ConvertToRaylibColor(Core::Color color);

 private:
  GameSettings settings;
  GameSession* session;
};
