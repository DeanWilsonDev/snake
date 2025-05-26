#pragma once
#include "game-settings.h"
#include "game-session.h"
#include "irenderer.h"

class Color;

struct RaylibRendererParams {
  GameSettings settings;
  GameSession* session;
};

class RaylibRenderer : public IRenderer {
 public:
  RaylibRenderer(const RaylibRendererParams& params);
  ~RaylibRenderer() = default;

  void beginDrawing() override;
  void stopDrawing() override;
  void clearBackground(Color color) override;
  void draw() override;

 private:
  GameSettings settings;
  GameSession* session;
};
