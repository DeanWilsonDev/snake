#pragma once
#include "game-settings.h"
#include "game-state.h"
#include "irenderer.h"

class Color;

struct RaylibRendererParams {
  GameSettings settings;
  GameState* state;
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
  GameState* state;

};
